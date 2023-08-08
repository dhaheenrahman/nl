#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int numPackets, bucketSize, outputRate;

    printf("Enter the number of packets: ");
    scanf("%d", &numPackets);

    printf("Enter the bucket size: ");
    scanf("%d", &bucketSize);

    printf("Enter the output rate: ");
    scanf("%d", &outputRate);

    int currentBucketSize = 0;
    int inputPackets[numPackets];

    printf("Enter the packet sizes:\n");
    for (int i = 0; i < numPackets; i++) {
        printf("Packet %d: ", i + 1);
        scanf("%d", &inputPackets[i]);
    }

    for (int i = 0; i < numPackets; i++) {
        printf("\nIncoming packet: %d\n", inputPackets[i]);
        printf("Current bucket size: %d\n", currentBucketSize);

        if ((currentBucketSize + inputPackets[i]) <= bucketSize) {
            currentBucketSize += inputPackets[i];
            printf("Packet accepted.\n");
        } else {
            printf("Packet dropped.\n");
        }

        sleep(1); // Simulating packet processing time

        if (currentBucketSize > 0) {
            int outputPackets = (currentBucketSize > outputRate) ? outputRate : currentBucketSize;
            printf("Outgoing packet: %d\n", outputPackets);
            currentBucketSize -= outputPackets;
        } else {
            printf("No packets to transmit.\n");
        }
    }

    return 0;
}

