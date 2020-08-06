#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../stdio.h"
#include "./mem.h"

size_t __strlen(const char* str)
{
	size_t return_val = 0; 
	while (*(str + return_val)) return_val++;
	return return_val;
}

char* __strncat(char* dest, const char* src, size_t num)          
{ 
	char* end_dest = dest + __strlen(dest);

	for (size_t i = 0; i < num && src[i]; i++)
		end_dest[i] = src[i];

	return dest;
}

char* __strcat(char* dest, const char* src)                       
{ 
	// Don't know if I should be doing this, but it'll do the job for now.
	return __strncat(dest, src, -1);
}

char* __strstr(char* scan, char* sequence)
{
	size_t sequ_length = __strlen(sequence);

	for (; *scan; scan++)
	{
		size_t match = 0;
		for (size_t j = 0; j < sequ_length; j++) if (*(scan + j) == sequence[j]) match++;
		if (match == sequ_length) return scan;
	}

	return NULL;
}

int __strcmp(const char* str1, const char* str2)
{
	// Implementation taken from musl
	for (; *str1==*str2 && *str1; str1++, str2++);
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

const char* __strchr(const char* scan, int character)
{
	for (; *scan != character; scan++)
		if (character != '\0' && *scan == '\0')
			return NULL;
		
	return scan;
}

// [bjrkk] FIXME: Probably a bad idea...
char* __strcpy(char* dest, const char* src) 
{ 
	return (char*)__memcpy(dest, src, __strlen(src) + 1);
} // I think this is how gclib does it? With the +1? 


/* FIXME the strspn & strcspn functions are better done
 * with lookup tables */
size_t* __strspn (const char *str, const char *chars)
{ // This is probably terrible.
	int count = 0;
	do 
	{
		if (str[count] != chars[count]) return count;
		count++;
	} while (count <= sizeof(chars));
}

size_t* __strcspn(const char *str, const char *chars)
{ // THIS IS GUARANTEED TERRIBLE
	int str_i = 0;
	int chars_i = 0;
	do
	{
		if (str[str_i] == chars[chars_i]) return str_i;
		str_i++;
		if (str_i >= sizeof(chars))
		{
			str_i = 0;
			chars_i++;	
		}	
	} while (str_i <= sizeof(chars));	
}

/*
Non-standard functions.
Only for internal use (?)
*/
char* __strupr(char* str)
{
	for (; *str; str++)
	{
		char c = *str;
		if (c >= 'a' && c <= 'z') c -= 32;
		*str = c;
	}
	
	return str;
}

char* __strlwr(char* str)
{
	for (; *str; str++)
	{
		char c = *str;
		if (c >= 'A' && c <= 'Z') c += 32;
		*str = c;
	}

	return str;
}
