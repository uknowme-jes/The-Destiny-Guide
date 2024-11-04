const express = require("express");
const { exec } = require("child_process");
const path = require("path");

const app = express();
const PORT = 3000;

// Serve static files from the 'website' folder
app.use(express.static(path.join(__dirname, "website")));

// Route to run the speak.py file
app.get("/run-python", (req, res) => {
  exec("python Readings/speak.py", (error, stdout, stderr) => {
    if (error) {
      console.error(`Error: ${error.message}`);
      return res
        .status(500)
        .send("An error occurred while running the script.");
    }
    if (stderr) {
      console.error(`stderr: ${stderr}`);
      return res.status(500).send("Script encountered an error.");
    }
    console.log(`stdout: ${stdout}`);
    res.send("Python script executed successfully!");
  });
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
