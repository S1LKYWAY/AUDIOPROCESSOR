# Audio Processing Application

## Author
Qasim Abbas

## Overview
This application is designed to load and visualize stereo PCM audio data from WAV files. It utilizes the Qt framework for the graphical user interface and provides features such as loading WAV files, drawing waveforms, and calculating the entropy of the audio data.

## Features
- **WAV File Loading**: The application allows users to load WAV files, reading and validating the file header for PCM audio format and stereo channels.

- **Waveform Visualization**: Once a WAV file is loaded, the application visualizes the stereo waveforms, drawing them on the main window.

- **Entropy Calculation**: The application calculates and outputs the entropy of the combined audio samples, providing insights into the randomness or predictability of the audio data.

## Entropy Calculation
The entropy calculation is based on the Shannon entropy formula:

\[ H(X) = - \sum_{i} P(x_i) \cdot \log_2(P(x_i)) \]

Where:
- \( H(X) \) is the entropy.
- \( P(x_i) \) is the probability of occurrence of each unique audio sample value \( x_i \).

The application uses the calculated entropy to provide a quantitative measure of the complexity of the audio data.

## How to Use
1. **Compile**: Ensure you have the necessary dependencies installed and compile the application using your preferred compiler.

2. **Run**: Execute the compiled executable.

3. **Load WAV File**: Use the application to load a stereo WAV file. The application will read the file header and validate the audio format and channel count.

4. **Waveform Visualization**: Once the file is loaded, the stereo waveforms will be drawn on the main window.

5. **Entropy Output**: The application will output the calculated entropy of the combined audio samples to the console.

## Dependencies
- Qt Framework: Ensure you have the necessary Qt libraries installed to build and run the application.

## Notes
- This code is provided as-is, and any modifications or improvements are welcome.
