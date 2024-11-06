import subprocess

# Your condition
condition_met = True  # Replace this with your actual condition

# Check the condition and run temp.py if it’s met
if condition_met:
    subprocess.run(["python", "Readings/fatigue_detection.py"])
