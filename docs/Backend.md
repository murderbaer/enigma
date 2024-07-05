# Backend

The backend is written in C and is using CMake as its build system. A small introduction is given in the docs folder on how to build the project using CMake. 

## Modes
The backend can be viewed as 3 smaller programs. The core of all three parts is the enigma component. All 3 modes use this enigma component to provide different behaviors, controlled by command-line-arguments. 
Running `./build/enigma` or `./build/enigma -h # --help` lists all available arguments.

### CLI
The CLI component was created to have an easy way to debug the functionality of the enigma component. It is possible to configure an entire enigma using command-line-arguments or using the interactive mode. The interactive mode is activated by running the program like `enigma -i/--interactive`. You will be asked for each configurable option on how you want to set it.
Another way to use the CLI is by configuring all options using CLI arguments. An example is provided in the root of the project. 

#TODO add file

### Server
As graphical interfaces tend to be rather complex to create in pure C and as I also have a background as a Web-Developer I made the choice to create the frontend in React. This means that the business logic need to be able to communicate to the Frontend. A rudimentary server was implemented being able to receive a JSON formatted enigma configuration and deliver the en/decoded text back. 

#TODO check if more features were implemented. 

### Cyclometer
The cyclometer component creates the cycles and counts them for the given enigma configurations. To learn more about the Cyclometer read the [documentation](Cyclometer.md).


## The enigma component
### Rotor
The Rotors are currently predefined and hardcoded as a string. A shortened example of this string would be "CDAB". A would be converted to C, as the letter C is in the first (A) position. B would be converted to a D, A to C and B to D. 

To recreate the behavior of a rotor it first needs to be broken down. The base idea is that if I have a letter 'X' as as the input, I get another letter 'Y' as the output. This behavior needs to exists for every letter in the alphabet. The most obvious approach would be to create some sort of map like: 
'A' => 'C', 'B' => 'D', 'C' => 'A', 'D' => 'B'

Where the left value is the input and the right value the output. A similar approach was used. First the Rotor string definition and the Text to decrypt were converted to integer arrays. Using the short example from above the array would look like `[2,3,0,1]`. If `ABC` was chosen as the text to encrypt, the corresponding int array would look like `[0,1,2]`. Those conversion are relative simple operations as in C a string is just a char array and an char ist just a short which can be used for calculation.

```C
int *get_int_array_from_string(char *str, int size)
{
    int *array = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        array[i] = str[i] - 'A';
    }

    return array;
}
```
The above example ist the code on how those conversions are made. `'A'` is an ASCII encoded character and its numerical value is 65. So if `str[i]` equals to `A` the value in `array[i]` would be 0. `B` would result in 1 etc.

**_NOTE:_** One condition to the code is that all letters have to be uppercase. If any extensions to the project are made, please keep this in mind. There is an `to_upper_case` method which should be used before.

The big advantage to this approach is, that now the index of the rotor array is the input and the containing value the output. The input string is the int array the text input (`[0,1,2]`). Each element of the array is one index for the rotor, so looping through the entire array and using the values as the index value for the rotor will return an encoded value. The enigma uses multiple rotors, so instead of returning the encoded value immediately, it will pass other rotors before returning back to the user.

As C also does not have a native Map structure the implementation of one is now not necessary. Also getting an item from an array should be always faster than from a Map as it doesn't really get any simpler than that.

The last important thing is understanding how to rotate the rotors. As they are represented as an int array, the first solutions could be to just shift the array. Although possible, this would require to enter a for loop for each letter (26 times) and for each rotation. For smaller texts this would not be a problem but especially for the cyclometer where over 100.000 configurations would need to be tested, the impact would be noticeable.

Instead of rotating the array, an was offset is introduced. This offset is increased before a letter is being encrypted being applied to the letter by subtracting it.
```c
int encrypted_letter = rotor[letter_index - offset]; // Mock-Code
```



### Reflector
The Reflector works basically the same as a Rotor but it doesn't rotate.

### Plugboard
The plugboard is defined as pairs of char which represent the letters to switch 'AB CD'. Some checks are done so no invalid options are allowed ('AB AC' is not valid). At first an array with 26 entries is defined. Each cell holds its index as its value. If the plugboard is defined correctly, the array will be modified by switching the index values in the cells according to the definition. Example:
```C
[0,1,2,3,4,5] // initially
[1,0,3,2,4,5] // A and B switch positions and C and D too
```
As the input is also an int array, each element of that array is being sent through the plugboard_array, possibly being modified. This happen 2 time for each complete enigma encryption. First, at the very and last at the very end of the encryption process.
