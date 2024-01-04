#include "enigma.h"
#include <stdio.h>
#include <string.h>

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};
/*
int main() {
	char e[4][27];
	char r[5];
	int numR = 0;
	char msg[1024];
	char eMsg[1024];
	char dMsg[1024];
	int rotations = 0;
	printf("Enter message: ");
	Get_Message(msg);
	printf("Enter rotors: ");
	numR = Get_Which_Rotors(r);
	printf("Enter rotations: ");
	rotations = Get_Rotations();
	Set_Up_Rotors(e, r);
	Apply_Rotation(rotations, e);
	Encrypt(e, numR, msg, eMsg);
	Decrypt(e, numR, msg, dMsg);
	printf("Encrypted String: %s\nDecrypted String: %s\n", eMsg, dMsg);
}
*/

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
	fgets(msg, 80, stdin);
	if (msg[strlen(msg) - 1] == '\n')
		msg[strlen(msg) - 1] = '\0';
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
	fgets(which_rotors, 5, stdin);
	if (which_rotors[strlen(which_rotors) - 1] == '\n')
		which_rotors[strlen(which_rotors) - 1] = '\0';
    return strlen(which_rotors);
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
	int num = 0;
        scanf("%d", &num);
	return num;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
	char rotor = 'a';
	for (int i = 0; i < 4; i++) {
		if (which_rotors[i] != '\0') {
			rotor = which_rotors[i];
			strcpy(encryption_rotors[i], ROTOR_CONSTANTS[atoi(&rotor)]);
		} else {
			encryption_rotors[i][0] = '\0';
		}
	}
    return;
}

void rotate(char str[]) {
	char temp = str[strlen(str) - 1];
	for (int i = strlen(str) - 1; i > 0; i--) {
		str[i] = str[i - 1];
	}
	str[0] = temp;
	return;
}

// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < rotations; j++) {
			rotate(encryption_rotors[i]);
		}
	}
    return;
}

int findIndex(char c, char rotor[]) {
	for (int i = 0; i < strlen(rotor); i++) {
		if (rotor[i] == c) {
			return i;
		}
	}
	return -1;
}
// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
	int i = 0;
	for (i = 0; i < strlen(msg); i++) {
		char changed = msg[i];
		//printf("%d%s\n", i, encrypted_msg);
		for (int j = 0; j < num_active_rotors; j++) {
			if (changed == ' ')
				break;
			changed = encryption_rotors[j][(int)changed - 65];
			//printf("%d%s\n", i, encrypted_msg);
		}
		encrypted_msg[i] = changed;
		//printf("%d%s\n", i, encrypted_msg);
	}
	encrypted_msg[i] = '\0';
    return;
}

// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
	int i = 0;
	for (i = 0; i < strlen(encrypted_msg); i++) {
		char changed = encrypted_msg[i];
		for (int j = num_active_rotors - 1; j >= 0; j--) {
			if (changed == ' ')
				break;
			changed = (char)(findIndex(changed, encryption_rotors[j]) + 65);
			//printf("%c", changed);
		}
		decrypted_msg[i] = changed;
		//printf("\n%s\n", decrypted_msg);
	}
	decrypted_msg[i] = '\0';
    return;
}


