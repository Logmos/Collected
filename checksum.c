/* Internet checksum's implementation, used to ensure integrity and securuty
 * of data during internet transmission. 
 * Here is its elementary thought :
 * ____________________________________
 *
 *   Binary                 Hexadecimal
 * ____________________________________
 *
 *   1001 0001 1001 0100    9194
 *
 *   1000 0000 0111 0011    8073
 *
 *                             +
 *
 * 1 0001 0010 0000 0111    11207
 * |                   1
 * |                   ^
 * |___________________|
 * 0 0001 0010 0000 1000    1208
 *            .
 *            .
 *            .
 *_____________________________________
 *
 * Until all data is added we get the checksum.
 */
#include <stdio.h>

/* User-defined data type, which can be adjusted to meet actual
 * requirement */
struct data {
    int a;
    int b;
    int c;
} buff;

/* Checksum-field should be 0 when checksum() is executed for the first
 * time, then the checksum generated is wrapped in the struct data to be
 * transmitted over internet, waiting for a second call of ckecksum(),
 * after which 0 is necessarily generated from checksum() if the data is
 * safe and sound */
unsigned short checksum(unsigned char *arr, int count)
{
    int sum = 0;
    while (count > 1) {
        sum += *(unsigned short *) arr;
        arr += 2;
        count -= 2;
    }   

    if (count > 0)
        sum += *(unsigned short *) arr;

    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

int main(int argc, char *argv[])
{
    buff.a = 1;
    buff.b = 2;
    buff.c = checksum(&buff, sizeof(buff));
    printf("%hu\n", buff.c);
    printf("%hu\n", checksum(&buff, sizeof(buff)));
    return 0;
}
