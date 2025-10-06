import os
import datetime
import random
import locale

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///bank.db")

locale.setlocale(locale.LC_ALL, "en_US.UTF-8")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def dashboard():

    # Query for login activity
    rows = db.execute("SELECT * FROM session WHERE id = ? ORDER BY time DESC", session["user_id"])

    # Query for users cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    # Convert cash to dollars
    cash[0]["cash"] = locale.currency(cash[0]["cash"], grouping=True)

    return render_template("dashboard.html", rows=rows, cash=cash[0]["cash"])


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Query to track login activity
        db.execute("INSERT INTO session VALUES (?,?,?)", datetime.datetime.now(), "Login", session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password does not match", 400)

        # Query for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure that there is only one unique username
        if len(rows) != 0:
            return apology("username has been taken", 400)

        # Creates a unique account number
        while True:
            accountnumber = random.randint(100000,999999)
            rows = db.execute("SELECT * FROM users WHERE accountnumber = ?", accountnumber)

            if len(rows) == 0:
                break

        # Encrypt password
        password_hash = generate_password_hash(request.form.get("password"))

        # Query insert encrypted password and username
        db.execute(
            "INSERT INTO users (username, hash, length, accountnumber) VALUES (?,?,?,?)",
            request.form.get("username"),
            password_hash,
            len(request.form.get("password")), accountnumber,
        )

        # Query for newly inserted user
        rows = db.execute("SELECT * FROM users WHERE hash = ?", password_hash)

        # Remember which user is logged in
        session["user_id"] = rows[0]["id"]

        # Query to track login activity
        db.execute("INSERT INTO session VALUES (?,?,?)", datetime.datetime.now(), "Login", session["user_id"])
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/transfer", methods=["GET", "POST"])
@login_required
def transfer():
    """Send money to other users"""
    if request.method == "POST":
        # Query for information on user
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure user is able to verify identify
        if request.form.get("username") != rows[0]["username"] or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("Failed to verify identify", 400)

        # Create list of registered users in database
        users = []
        rows = db.execute("SELECT * FROM users")
        for row in rows:
            users.append(row["accountnumber"])

        # Query for information on user
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Removes the current user from the list
        users.remove(rows[0]["accountnumber"])

        # Ensure account number is in database and is valid
        if not request.form.get("accountnumber").isdigit() or not int(request.form.get("accountnumber")) in users:
            return apology("Invalid Account Number", 400)
        # Ensure cash submitted is available and valid
        if request.form.get("amount").find("$") != -1:
            return apology("Remove the dollar sign", 400)
        elif not request.form.get("amount") or float(request.form.get("amount")) < 0.01:
            return apology("Invalid amount of money", 400)
        elif rows[0]["cash"] < float(request.form.get("amount")):
            return apology("Insufficient Funds", 400)

        # Query for updating cash of the sender and receiver
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", float(request.form.get("amount")), session["user_id"])
        db.execute("UPDATE users SET cash = cash + ? WHERE accountnumber = ?", float(request.form.get("amount")), request.form.get("accountnumber"))


        # Query to add transaction to history
        receiver = db.execute("SELECT * FROM users WHERE accountnumber = ?", request.form.get("accountnumber"))
        sender = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        db.execute("INSERT INTO history (id, time, receiver, sender, amount) VALUES (?,?,?,?,?)", session["user_id"], datetime.datetime.now(), receiver[0]["username"], sender[0]["username"], 0 - float(request.form.get("amount")))
        db.execute("INSERT INTO history (id, time, receiver, sender, amount) VALUES (?,?,?,?,?)", receiver[0]["id"], datetime.datetime.now(), receiver[0]["username"], sender[0]["username"], request.form.get("amount"))

        return redirect("/")
    else:
        return render_template("e-transfer.html")


@app.route("/history", methods=["GET"])
@login_required
def history():
    """history of transactions"""

    # Query for user transaction history
    rows = db.execute("SELECT * FROM history WHERE id = ? ORDER BY time DESC", session["user_id"])

    # Loops through history and converts amount to currency
    for row in rows:
        row["amount"] = locale.currency(row["amount"], grouping=True)

    return render_template("history.html", rows=rows)


@app.route("/support", methods=["GET", "POST"])
@login_required
def support():
    """Contact support"""
    if request.method == "POST":
        # Verify user submitted valid email address
        if not request.form.get("email") or "@" not in request.form.get("email"):
            return apology("Invalid Email", 400)
        # Verify user submitted a name
        elif not request.form.get("name"):
            return apology("Must provide a name", 400)
        # Verify user submitted a description
        elif not request.form.get("description"):
            return apology("Must provide a description", 400)

        # Query to add users submission into inquiries
        db.execute("INSERT INTO inquiries VALUES (?,?,?,?)", session["user_id"], request.form.get("email"), request.form.get("name"), request.form.get("description"))

        return redirect("/")

    return render_template("support.html")


@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    # Query for user information
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    # Converts password into *
    password = ""
    for i in range(int(rows[0]["length"])):
        password += "*"

    return render_template(
        "profile.html", password=password, name=rows[0]["username"], accountnumber=rows[0]["accountnumber"]
    )


@app.route("/logout")
def logout():
    """Log user out"""

    # Query to track login activity
    db.execute("INSERT INTO session VALUES (?,?,?)", datetime.datetime.now(), "Log Out", session["user_id"])

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


if __name__ == "__main__":
    app.run(debug=True, port=5000)
