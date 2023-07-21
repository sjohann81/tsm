#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int is_number(char *str) 
{
	char v;
	
	if (*str == 0) return 0;
	
	if (*str == '\'') {
		if (*(str + 1) == 0) return 0;
		return 1;
	}
	
	if (*str == '0') {
		v = *(str + 1);
		
		if (v == 'x') {
			str += 2;
			
			while (*str) {
				if (!isxdigit(*str++))
					return 0;
			}
		} else {
			str++;

			while (*str) {
				if (*str < '0' && *str > '7')
					return 0;
				str++;
			}
		}
		
		return 1;
	}

	if (*str == '+' || *str == '-')
		str++;
	
	while (*str) {
		if (!isdigit(*str++))
			return 0;
	}
	
	return 1;
}


int to_number(char *str)
{
	char *endptr;
	char v;
	
	if (*str == 0) return 0;
	
	if (*str == '\'') {
		if (*(str + 1) == 0) return 0;
		
		return *(str + 1);
	}
	
	if (*str == '0') {
		v = *(str + 1);
		
		if (v == 'x') {
			str += 2;
			
			return strtol(str, &endptr, 16);
		} else {
			if (v >= '0' && v <= '7') {
				str++;
				
				return strtol(str, &endptr, 8);
			} else
				return 0;
		}
	}
	
	return atoi(str);
}
