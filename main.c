#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//WAV header definition
typedef struct {
    char RIFF[4];      
    uint32_t fileSize;    
    char WAVE[4];        
    char fmt[4];  
    uint32_t fmtSize;
    uint16_t audioFormat;  
    uint16_t numChannels;  
    uint32_t sampleRate;   
    uint32_t byteRate;     
    uint16_t blockAlign;
    uint16_t bitsPerSample; 
    char data[4];  
    uint32_t dataSize; 
} WAVHeader;

//WAV file struct
typedef struct {
    WAVHeader header;        
    int16_t* samples;        
    int sampleCount;         
} WAVFile;

int main(int argc, char* argv[]) 
{
    WAVFile wavFile;
    
    if (argc != 4) {
        printf("Uso: %s pedropedrope.wav output.wav factor\n", argv[0]);
        return 1;
    }
    
    //Open the input file
    FILE* inputFile = fopen(argv[1], "rb");
    if (inputFile == NULL) 
    {
        printf("Error al abrir el archivo de entrada :c\n");
        return 1;
    }

    //Read the WAV header
    fread(&wavFile.header, sizeof(WAVHeader), 1, inputFile);

    //Open the outputfile
    FILE* outputFile = fopen(argv[2], "wb");
    if (outputFile == NULL) 
    {
        printf("Error al abrir el archivo de salida :c\n");
        free(wavFile.samples); 
        return 1;
    }

    //Write the header to the outputfile
    fwrite(&wavFile.header, sizeof(WAVHeader), 1, outputFile); 


    //Determine the number of samples
    wavFile.sampleCount = wavFile.header.dataSize / sizeof(int16_t);
    wavFile.samples = (int16_t*)malloc(wavFile.header.dataSize);

    //Read the samples from the audio
    fread(wavFile.samples, wavFile.header.dataSize, 1, inputFile);

    fclose(inputFile);


    float factor = atof(argv[3]);

    //Modifying the volume
    for (int i = 0; i < wavFile.sampleCount; i++) {
        int32_t newSample = (int32_t)(wavFile.samples[i] * factor);

        //Check and correct overflows
        if (newSample > INT16_MAX) {
            newSample = INT16_MAX;
        } else if (newSample < INT16_MIN) {
            newSample = INT16_MIN;
        }

        wavFile.samples[i] = (int16_t)newSample; 
    }

    //Write the samples in the outputfile
    fwrite(wavFile.samples, wavFile.header.dataSize, 1, outputFile); 

    fclose(outputFile); 

    free(wavFile.samples);

    printf("Volumen modificado exitosamente :D!\n");
    return 0;
}
