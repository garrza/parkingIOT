USE `parking-db`;  -- Make sure you're using the correct database

-- Insert sample students
INSERT INTO Students (student_id, first_name, last_name, email, phone_number)
VALUES
  ('7CD1D2DB', 'Eugenio', 'Garza Sada', 'eugenio.garzasada@example.com', '1234567890'),
  ('FA8E0C7D', 'Hervey', 'Navarro', 'hervey.navarro@example.com', '9876543210'),
  ('89E42216', 'Bob', 'Johnson', 'bob.johnson@example.com', '5555555555'),
  ('74B58F04', 'Alice', 'Williams', 'alice.williams@example.com', '3333333333'),
  ('EA872380', 'Charlie', 'Brown', 'charlie.brown@example.com', '1111111111');

INSERT INTO AuthorizedCars (owner_id, plate_number, make, model, color)
VALUES
  ('7CD1D2DB', 'ABC123', 'Toyota', 'Camry', 'Blue'),
  ('FA8E0C7D', 'XYZ789', 'Honda', 'Civic', 'Red'),
  ('89E42216', '123ABC', 'Ford', 'Focus', 'Green'),
  ('74B58F04', '456XYZ', 'Chevrolet', 'Malibu', 'Silver'),
  ('EA872380', '789123', 'Nissan', 'Altima', 'Black');