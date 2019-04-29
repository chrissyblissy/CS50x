import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT stock, number FROM transactions WHERE id = :userid", userid=session.get("user_id"))
    user_cash = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session.get("user_id"))[0]
    all_total = user_cash['cash']

    # create portfolio of what the user currently owns
    updated_portfolio = []
    for dictionary in portfolio:
        appended = False
        for item in updated_portfolio:
            if dictionary['stock'] == item['stock']:
                item['number'] += dictionary['number']
                appended = True
        if appended == False:
            updated_portfolio.append(dictionary)

    updated_portfolio[:] = [d for d in updated_portfolio if d.get('number') != 0]


    for item in updated_portfolio:
        # create all columns for table
        item['name'] =  lookup(item['stock'])['name']
        item['price'] = lookup(item['stock'])['price']
        item['total'] = item['price'] * item['number']
        all_total += item['total']
        # manipulate into correct format
        item['price'] = usd(item['price'])
        item['total'] = usd(item['total'])
        item['stock'] = item['stock'].upper()



    user_cash['cash'] = usd(user_cash['cash'])
    all_total = usd(all_total)
    return render_template("index.html", updatedportfolio=updated_portfolio, cash=user_cash['cash'], alltotal=all_total)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method =="POST":

        # variables that are used multiple times
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not lookup(symbol):
            return apology("Incorrect stock symbol", 400)
        price = lookup(symbol)['price']

        if not symbol:
            return apology("You must provide a stock symbol", 400)

        if not shares:
            return apology("You must provide a number", 400)
        try:
            int(shares)
        except ValueError:
            return apology("Stock must be an integer", 400)


        shares = int(shares)

        user_id=session.get("user_id")
        result = db.execute("SELECT cash FROM users WHERE id = :userid", userid=user_id)[0]

        if result['cash'] > (price * shares):
            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :userid", cost = price * shares, userid=user_id)
            db.execute("INSERT INTO transactions (id, stock, price, number) VALUES(:userid, :stock, :stockprice, :number)", userid=user_id, stock=symbol, stockprice=price, number=shares)


        else:
            return apology("Cannot afford", 400)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT stock, number, price, time FROM transactions WHERE id = :userid", userid=session.get("user_id"))
    print(history)
    for item in history:
        item['price'] = usd(item['price'])
        item['stock'] = item['stock'].upper()
    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Must provide a company's symbol", 400)


        company_data = lookup(request.form.get("symbol"))

        if not company_data:
            return apology("Invalid symbol", 400)

        return render_template("quoted.html", name=company_data['name'], symbol=company_data['symbol'], price=usd(company_data['price']))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    """Register user for website."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method =="POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("you must provide a username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("you must provide a password", 400)

        # Ensure password match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Hashes the users password
        hashpassword = generate_password_hash(request.form.get("password"))

        # Inserts the users username and password into the 'users' table in the database
        result = db.execute("INSERT INTO users (username, hash) Values(:username, :hash)", username=request.form.get("username"), hash=hashpassword)
        if not result:
            return apology("That username has been taken")

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        #Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id=session.get("user_id")

    if request.method =="POST":

        # variables that are used multiple times


        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
#        if not lookup(symbol):
#            return apology("Incorrect stock symbol", 403)


        if not symbol:
            return apology("You must provide a stock symbol", 400)

        if not shares:
            return apology("You must provide a number", 400)

        try:
            int(shares)
        except ValueError:
            return apology("Stock must be an integer", 400)


        shares = int(shares)
        symbol = request.form.get("symbol").lower()
        price = lookup(symbol)['price']

        stock_check = db.execute("SELECT number FROM transactions WHERE id = :userid AND stock = :stocksymbol", userid=user_id, stocksymbol=symbol)
        cash_check = db.execute("SELECT cash FROM users WHERE id = :userid", userid=user_id)[0]
        stock_total = 0
        for purchase in stock_check:
            stock_total += purchase['number']
        if stock_total >= shares:
            db.execute("UPDATE users SET cash = cash + :cost WHERE id = :userid", cost = price * shares, userid=user_id)
            db.execute("INSERT INTO transactions (id, stock, price, number) VALUES(:userid, :stock, :stockprice, :number)", userid=user_id, stock=symbol, stockprice=price, number=-shares)


        else:
            return apology("Not enough shares", 400)

        return redirect("/")

    else:

        choices = db.execute("SELECT stock, number FROM transactions WHERE id= :userid", userid=user_id)
        condensed_choices = []

        for dictionary in choices:
            exists = False
            for item in condensed_choices:
                if dictionary['stock'].upper() == item['stock']:
                    item['number'] += dictionary['number']
                    exists = True
                    break
            if exists == False:
                dictionary['stock'] = dictionary['stock'].upper()
                condensed_choices.append(dictionary)

        condensed_choices[:] = [d for d in condensed_choices if d.get('number') != 0]
        return render_template("sell.html", condensedchoices=condensed_choices)



def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
