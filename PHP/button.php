<?php
// Check if the 'state' parameter is present in the GET request
if (isset($_GET['state'])) {
    $state = $_GET['state'];
    // Write the LED state to 'results.txt'
    $file = fopen("results.txt", "w");
    if ($file) {
        fwrite($file, $state);
        fclose($file);
        echo "<p>LED status updated to: $state</p>";
    } else {
        echo "<p>Could not update LED status.</p>";
    }
}

// Read the current state from 'results.txt'
$current_state = file_get_contents("results.txt");
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 LED Controller</title>
</head>
<body>
    <h1>Control ESP8266 LED</h1>
    <form method="GET" action="button.php">
        <button type="submit" name="state" value="ON">Turn LED On</button>
        <button type="submit" name="state" value="OFF">Turn LED Off</button>
    </form>

    <p>Current LED State: <?php echo htmlspecialchars($current_state); ?></p>
</body>
</html>
