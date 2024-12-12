<?php
// Database connection details
$servername = "localhost";
$username = "u699644480_db_ChrisCampbe";
$password = "Mk-18Mjolnir";
$database = "u699644480_ChrisCampbell";

// Connect to the database
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Query to fetch the latest 15 potentiometer values
$sql = "SELECT timestamp, POT_value FROM potentiometer_table ORDER BY timestamp DESC LIMIT 15";
$result = $conn->query($sql);

// Prepare the response
$data = array();
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
}

// Return the data as JSON
header('Content-Type: application/json');
echo json_encode($data);

// Close the connection
$conn->close();
?>
