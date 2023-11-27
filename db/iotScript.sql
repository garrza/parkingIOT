CREATE DATABASE IF NOT EXISTS parking_db;

-- Select the database
USE parking_db;

-- Table for students
CREATE TABLE IF NOT EXISTS Students (
    student_id VARCHAR(20) PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone_number VARCHAR(15)
);

-- Table for authorized cars
CREATE TABLE IF NOT EXISTS AuthorizedCars (
    owner_id VARCHAR(20) PRIMARY KEY,
    plate_number VARCHAR(20) UNIQUE NOT NULL,
    make VARCHAR(50) NOT NULL,
    model VARCHAR(50) NOT NULL,
    color VARCHAR(20),
	FOREIGN KEY (owner_id) REFERENCES Students(student_id)
);

-- Table for currently parked cars
CREATE TABLE IF NOT EXISTS CurrentlyParked (
    student_id VARCHAR(20) PRIMARY KEY,
    parked_time DATETIME,
    parking_location VARCHAR(100),
    FOREIGN KEY (student_id) REFERENCES Students(student_id)
);