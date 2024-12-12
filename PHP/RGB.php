
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RGB Slider</title>
    <style>
        .slider-container {
            margin: 20px 0;
        }
        .slider-label {
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h1>RGB Slider</h1>
    <form action="" method="post">
        <div class="slider-container">
            <label for="red" class="slider-label">Red:</label>
            <input type="range" id="red" name="red" min="0" max="255" value="0" oninput="updateValue('redValue', this.value)">
            <span id="redValue">0</span>
        </div>
        <div class="slider-container">
            <label for="green" class="slider-label">Green:</label>
            <input type="range" id="green" name="green" min="0" max="255" value="0" oninput="updateValue('greenValue', this.value)">
            <span id="greenValue">0</span>
        </div>
        <div class="slider-container">
            <label for="blue" class="slider-label">Blue:</label>
            <input type="range" id="blue" name="blue" min="0" max="255" value="0" oninput="updateValue('blueValue', this.value)">
            <span id="blueValue">0</span>
        </div>
        <button type="submit" name="submit">Save RGB</button>
    </form>

    <script>
        function updateValue(id, value) {
            document.getElementById(id).innerText = value;
        }
    </script>

    <?php
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $red = isset($_POST['red']) ? intval($_POST['red']) : 0;
        $green = isset($_POST['green']) ? intval($_POST['green']) : 0;
        $blue = isset($_POST['blue']) ? intval($_POST['blue']) : 0;

        // Combine RGB values into a string
        $rgbData = "$red, $green, $blue";

        // Save RGB values to RGB.txt
        file_put_contents('RGB.txt', $rgbData);

        echo "<p>RGB values saved: $rgbData</p>";
    }
    ?>
</body>
</html>
