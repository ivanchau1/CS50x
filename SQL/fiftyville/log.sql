-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 and street = "Humphrey Street";

--Find transcript of interview of witnesses
SELECT transcript FROM interviews WHERE month = 7 AND day = 28;

--Find license plate, name and activity
SELECT bakery_security_logs.license_plate, bakery_security_logs.actiivty, people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 5 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.activity = "exit";

--Find account number, name and their transaction type
SELECT atm_transactions.account_number, people.name, atm_transactions.transaction_type FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";

--Find caller number, receiver number, and caller name
SELECT phone_calls.caller, people.name, phone_calls.receiver FROM phone_calls JOIN people ON people.phone_number = phone_calls.caller WHERE phone_calls.duration < 60 AND phone_calls.month = 7 AND phone_calls.day = 28;

--Find destination airport id
SELECT destination_airport_id FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE flights.month = 7 AND flights.day = 29 AND airports.city = "Fiftyville";

--Find destination airport location
SELECT * FROM airports JOIN flights ON flights.destination_airport_id = airports.id WHERE flights.destination_airport_id IN (SELECT destination_airport_id FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE flights.month = 7 AND flights.day = 29 AND airports.city = "Fiftyville") AND flights.month = 7 AND flights.day = 29 ORDER BY hour,minute DESC LIMIT 1;

--Find passport number of passengers on plane
SELECT passport_number FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE flights.id = 36;

--Find names on flight
SELECT people.name FROM people WHERE people.passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE flights.id = 36);

--Find criminal
SELECT name FROM people
WHERE name IN
(SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 5 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.activity = "exit")
AND name IN
(SELECT people.name FROM phone_calls  JOIN people ON people.phone_number = phone_calls.caller WHERE phone_calls.duration < 60 AND phone_calls.month = 7 AND phone_calls.day = 28)
AND name IN
(SELECT people.name FROM people WHERE people.passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE flights.id = 36))
AND name IN
(SELECT people.name FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw");

--Find Accomplice
SELECT phone_calls.caller, people.name, phone_calls.receiver FROM phone_calls JOIN people on people.phone_number = phone_calls.receiver WHERE phone_calls.duration < 60 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.caller = "(367) 555 5533";