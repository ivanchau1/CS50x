from cs50 import SQL
from flask import Flask, redirect, render_template

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
def index():
    """Show portfolio of stocks"""
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
def buy():
    """Buy shares of stock"""
    return render_template("buy.html")


@app.route("/history")
def history():
    """Show history of transactions"""
    return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
def quote():
    """Get stock quote."""

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
def sell():
    """Sell shares of stock"""
    return render_template("sell.html")
