# CS50 Bank
### Video Demo: https://youtu.be/I6FP9hRtcG8
### Project Description:
My project, CS50 Bank, is a web application developed with Flask that allows users to send and receive money from other users.

### HTML Files:
Utilizing the templating language, Jinja, I am able to create a file called layout.html as my template and insert elements into the template with other HTML files. In my project I created eight HTML files excluding the layout.html, which resembles the different pages on my web application.

#### apology.html
This file is directly from Problem Set 9: finance. When a user submits incorrect information in one of the forms, the apology.html page will be loaded with an image of an angry cat and a message letting the user know what input was inaccurate.

#### dashboard.html
In this file, I wanted to display the user's login activity and how much cash was available in their account. First, I added two containers by creating a class called "flex-container," and with the style.css file, I was able to create a box. The box on the left of the page contained the user's login activity. The login activity displayed a table with the date/time and the action (login or logout). To keep track of the login activity, I created an SQL database. When a user logs in, registers, or logs out, the time and action are logged in the database called "session." For the cash, I kept track of the user's cash with the SQL database called "users." When the user sent or received money, the database would be updated.

#### e-transfer.html
This file contains a form that verifies the user's identity by asking for the login details. In addition, it asks for the receiver's account number and the money to be transferred.

#### history.html
This file contains a table that displays the transactions the user has done. It shows the time, sender, receiver, and amount. With some JavaScript, when the user lost money, the amount would be red, and when the user gained money, the amount would be green.

#### layout.html
This file was directly from Problem Set 9: Finance. This layout included the title of the tabs, the navigation bar, and the elements included in the body of the website.

#### login.html
This file contains a form that allows a user to submit their login information.

#### profile.html
This file contains a table that displays the user's personal information. The information includes the user’s account number, username, and password (hidden with * symbol). The information comes from the database "users."

#### register.html
This file contains a form that allows a user to create an account by creating a username and password.

#### support.html
This file contains a form allowing the user to ask for assistance by submitting their email address, name, and the reason for submitting the form.

### Python File
The file “app.py” is a python file containing the different routes and displaying the HTML files based on the route the user goes. There are eight different routes.

#### /dashboard
It executes two queries for the user's cash and login activity and sends it to the dashboard.html file.

#### /login
Once users submit their information by POST, the cookie for the previous user is removed. Later, verifying that the user submitted a valid username and password. Once information is verified, a cookie for the user is created, and the login activity in the session database is updated.

#### /register
Once a user submits their information by POST, the cookie for the previous user is removed. Later, verifying that the user submitted a valid username and password. Once verification is complete, a six-digit account number is created, and their password is encrypted for security reasons. The username, encrypted password, and account number are added to the database users. A cookie is created for the user, and the login activity in the session database is updated.

#### /transfer
Once a user submits the information by POST, their information is verified. The username and password must match the current user; the account number must be in the database, excluding the current user, and the amount must be greater than $0.01. Once verification is complete, the cash for the sender and receiver is updated. In addition, the history database for the sender and receiver is updated. On the sender’s page, the amount will display red, and for the receiver, the amount will display green.

#### /history
A query that selects all user transaction history. A "for loop" converts the integer amount into currency and is sent to the history.html page.

#### /support
An SQL query selects the user's information. A “for loop” converts the user's password into "*". The user's information is sent to the profile.html template.

#### /logout
The login activity for the user is updated, and the cookie is removed.
