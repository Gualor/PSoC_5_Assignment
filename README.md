<p>
<img src="https://upload.wikimedia.org/wikipedia/it/b/be/Logo_Politecnico_Milano.png" alt="Logo of Politecnico di Milano" height="120" align="right">
Electronic Technologies and Biosensors Laboratory<br>A.Y. 2019/2020 – II Semester
</p>
<br>

# ASSIGNMENT 05: &emsp;PSoc I<sup>2</sup>C

<p>
This is the fifth assignment of the laboratory course of Electronic Technologies and Biosensors of Politecnico di Milano.
<br>
<br>
The assignment's objective was to design and implement electronic schematics and source code for 3 different projects regarding data retrieval, conversion and visualization by using 
<a href="https://it.wikipedia.org/wiki/I%C2%B2C">I<sup>2</sup>C communication</a>
between a master (<a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and">PSoC 5LP CY8CKIT-059 board</a>) and a slave (<a href="https://www.adafruit.com/product/2809">LIS3DH 3-axes accelerometer</a>).
</p>

## Workspace setup

Required software:
- PSoC Creator 4.3 (or later);
- Bridge Control Panel 1.20.0 (or later);
- CoolTerm (or any serial port monitor);

To get these projects up and running please follow few steps to properly setup the workspace:
>1. Clone the repository on your machine.
>2. Open PSoC Creator, go to *File* > *Open* > *Project/Workspace* and browse inside the folder *AY1920_II_HW_05_GUALNIERA_LORENZO* of the repository to find the main workspace file.
>3. Open the workspace file and set to *active* the desired project.
>4. Open Bridge Control, go to *Open commands file* and browse inside the folder *Bridge Control Panel* of the repository to select the .iic setting file.
>5. Now go to *Chart* > *Variable settings* > *Load* and browse inside the folder *Bridge Control Panel* of the repository to select the .ini setting file.
>6. (optional) You can also use CoolTerm (or any serial monitor) to inspect information regarding the registers settings of the LIS3DH setup by the microcontroller when booting up.

## Project 1

**Context:** &emsp;Implementing multiread and multiwrite functions.
> 1. Start from the final example (PSoC_03_Complete.zip) regarding the temperature sensor on the breakout board.
> 2. Add implementation of multiread and multiwrite functions in the I2C_Interface.c source file;
> 3. Substitute the single register readings in the for(;;) loop with a multiread.
> 4. Plot Temperature Data using Bridge Control Panel.

**Top design:** &emsp;Schematic and components information.
<p align="center">
<img src="https://i.imgur.com/MAqmCF3.png" alt="Top design project 1">
</p>

## Project 2

**Context:** &emsp;Testing the accelerometer output capabilities.
>1. Correctly set the control registers of the LIS3DH accelerometer to output 3 Axis accelerometer data in Normal Mode at 100 Hz in the ±2.0 g FSR.
>2. Read Output registers at a correct frequency (verify new Data is available using StatusReg information). Carefully think about the possible options to read data at a constant rate.
>3. Convert the 3 axial outputs of the Accelerometer to 3 right-justified 16-bit integers with the correct scaling (i.e. in mg).
>4. Correctly setup the UART Serial Communication: is the baud rate you chose sufficient to keep up with the data acquisition? Perform the correct calculations and add some comments regarding your choice in the TopDesign of the project.
>5. Send the values to be plotted to Bridge Control Panel.
>6. Save the Bridge Control Panel .ini and .iic files as “HW_05_SURNAME_NAME_A.ini” and “HW_05_SURNAME_NAME_A.iic”.

**Top design:** &emsp;Schematic and components information.
<p align="center">
<img src="https://i.imgur.com/efZ5bQk.png" alt="Top design project 2">
</p>

**Source code:**&emsp;The following pseudocode (in C flavour) briefly explains the general functioning of this project, for more details please open .c and .h files in a text editor to visualize useful comments and code description.

The main logic is subdivided between a main function, responsible for configuration of the LIS3DH and UART data transmission, and an interrupt service routine to handle syncronous data retrieval, conversion and packing in a 64-bit long message ready for transmission.

```c
int main(void)
{ 
	/* Write registers via I2C to set the following settings:
	 * -> FSR +-2g
	 * -> Data rate 100Hz
	 * -> 10-bit resolution
	 * -> Enable XYZ axial measurements */
	LIS3DH_Setup();
	Timer_Start(); // Trigger interrupt every 10ms
	ISR_Start(); // Enable the ISR
	packetReadyFlag = false;
	for(;;)
	{
		// New data is ready for transmission
		if (packetReadyFlag== true)
		{
			UART_Send(message); // Send new data over UART
			packetReadyFlag = false;
		}
	}
	return 0;
}
```
```c
void ISR(void)
{
	if (LIS3DH_isReady())
	{
		/* Read and process X axis value. */
		int x_val = LIS3DH_Read_X(); // Read X raw value
		x_val = RightAdjustVal(x_val); // Right adjust value
		x_val = MinMaxScaler(x_val, -512, 512, 2000, 2000) // Conversion to mg units

		/* Read and process Y axis value. */
		int y_val = LIS3DH_Read_Y(); // Read Y raw value
		y_val = RightAdjustVal(y_val); // Right adjust value
		y_val = MinMaxScaler(y_val, -512, 512, 2000, 2000) // Conversion to mg units

		/* Read and process Z axis value. */
		int z_val = LIS3DH_Read_X(); // Read Z raw value
		z_val = RightAdjustVal(z_val); // Right adjust value
		z_val = MinMaxScaler(z_val, -512, 512, 2000, 2000) // Conversion to mg units

		/* Pack XYZ axial data in a message. */
		message = LoadAxesData(x_val, y_val, z_val); // Packing data in 64-bit message
		packetReadyFlag = true; // New data ready for transmission
	}
}
```

## Project 3

**Context:** &emsp;Reading accelerometer output in m/s<sup>2</sup>.
>1. Correctly set the control register to output a 3 Axis Signal in High Resolution Mode at 100 Hz in the ±4.0 g FSR.
>2. Read Output registers at a correct frequency (verify StatusReg). As for Project 2, carefully think about the possible options to read data at a constant rate.
>3. Convert the 3 axial outputs of the Accelerometer to a floating point in m/s<sup>2</sup> units.
>4. Cast the floating point values to an int variable without losing information, keeping at least 3 decimals. What is a standard technique to perform such a task?
>5. Correctly setup the UART Serial Communication: is the baud rate you chose sufficient to keep up with the data acquisition? Perform the correct calculations and add some comments regarding your choice in the TopDesign of the project.
>6. Send the values to be plotted to Bridge Control Panel in m/s<sup>2</sup>.
>7. Save the Bridge Control Panel .ini and .iic files as “HW_05_SURNAME_NAME_B.ini” and “HW_05_SURNAME_NAME_B.iic”.

**Top design:** &emsp;Schematic and components information.
<p align="center">
<img src="https://i.imgur.com/uC4H0GP.png" alt="Top design project 3">
</p>

**Source code:**&emsp;The following pseudocode (in C flavour) briefly explains the general functioning of this project, for more details please open .c and .h files in a text editor to visualize useful comments and code description.

The main logic is subdivided between a main function, responsible for configuration of the LIS3DH and UART data transmission, and an interrupt service routine to handle syncronous data retrieval, conversion and packing in a 112-bit long message ready for transmission.

```c
int main(void)
{ 
	/* Write registers via I2C to set the following settings:
	 * -> FSR +-4g
	 * -> Data rate 100Hz
	 * -> 12-bit resolution
	 * -> Enable XYZ axial measurements */
	LIS3DH_Setup();
	Timer_Start(); // Trigger interrupt every 10ms
	ISR_Start(); // Enable the ISR
	packetReadyFlag = false;
	for(;;)
	{
		// New data is ready for transmission
		if (packetReadyFlag== true)
		{
			UART_Send(message); // Send new data over UART
			packetReadyFlag = false;
		}
	}
	return 0;
}
```
```c
void ISR(void)
{
	if (LIS3DH_isReady())
	{
		/* Read and process X axis value. */
		int x_val = LIS3DH_Read_X(); // Read X raw value
		x_val = RightAdjustVal(x_val); // Right adjust value
		x_val = MinMaxScaler(x_val, -2048, 2048, -4*GRAVITY, 4*GRAVITY) // Conversion to m/s^2 units

		/* Read and process Y axis value. */
		int y_val = LIS3DH_Read_Y(); // Read Y raw value
		y_val = RightAdjustVal(y_val); // Right adjust value
		y_val = MinMaxScaler(y_val, -2048, 2048, -4*GRAVITY, 4*GRAVITY) // Conversion to m/s^2 

		/* Read and process Z axis value. */
		int z_val = LIS3DH_Read_X(); // Read Z raw value
		z_val = RightAdjustVal(z_val); // Right adjust value
		z_val = MinMaxScaler(z_val, -2048, 2048, -4*GRAVITY, 4*GRAVITY) // Conversion to m/s^2 

		/* Pack XYZ axial data in a message. */
		message = LoadAxesData(x_val, y_val, z_val); // Packing data in 112-bit message
		packetReadyFlag = true; // New data ready for transmission
	}
}
```

## Additional resources

Useful documents/tutorials for the assignment:
* <a href="https://www.st.com/resource/en/datasheet/lis3dh.pdf">LIS3DH DATASHEET</a>
* <a href="https://www.cypress.com/file/177171/download">PSOC UART COMPONENT DATASHEET</a>
* <a href="https://www.cypress.com/file/175671/download">PSOC I2C MASTER COMPONENT DATASHEET</a>
* <a href="https://www.atlassian.com/git/tutorials">Atlassian Git Tutorial</a>
