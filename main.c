/*
 * Main
 *
 * Copyright (C) 2017 Group F Mail System Project
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <time.h>
#include "main.h"
#include "basicf.h"
#include "dataf.h"

int main(int argc, char const *argv[])
{
    data *startData;
    data *endData;
    backupdata *backup = (backupdata *) calloc(1, sizeof(backupdata));

    // costTime calculating
    clock_t beforeTime, afterTime;
    double costedTime;

    // Load data from file.
    //    beforeTime = clock();
    //    afterTime = clock();
    //    costedTime = (double) (afterTime - beforeTime) / CLOCKS_PER_SEC;
    //    printf("Succeed in %f s.\n", costedTime);

    // When data has been changed, add 1 to counter.
    int *changeCounter = (int *) calloc(1, sizeof(int));
    int dataNumber = 0;
    int exitCode;
    char *filePath;

    filePath = (char *) calloc(1, sizeof(char));

    ShowTitle();
    if (argv[1] == NULL)
    {
        printf("Please enter the path of data file.\n");
        printf("For example: \"%s GroupF.csv\"\n", argv[0]);
        printf("And we also defined \"%s .\" as \"%s data.csv\".\n", argv[0], argv[0]);
        return 0;
    }
    else if (strcmp(argv[1], ".") == 0)
    {
        strcpy(filePath, "data.csv");
    }
    else
    {
        strcpy(filePath, argv[1]);
    }

    exitCode = LoadData(filePath, &startData, &endData, &dataNumber);

    if (exitCode == 0)
        return 0;

    while(exitCode != -1)
    {
        ClearScreen();
        ShowTitle();
        ShowMain(*changeCounter);
        exitCode = MainOperation(GetOperation(), changeCounter, startData, endData, &dataNumber, backup, filePath);
    }

    free(filePath);
    FreeData(startData, endData);
    return 0;
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Get operation code from standard input.
 * @return {int} operation code
 */
int GetOperation()
{
    int operateCode = 0;

    printf(">");
    FlushBuffer();
    scanf("%d", &operateCode);

    return operateCode;
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Call defined UI function by operation code.
 * @param {int} operateCode operation code from user.
 * @param {int} changeCounter the redo menu will be displayed after data changed.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int*} dataNumber the number of data.
 * @return {int} operateCode exit = -1, stay = else.
 */
int MainOperation(int operateCode, int *changeCounter, data *startData, data *endData, int *dataNumber,
                  backupdata *backup, char *filePath)
{
    switch(operateCode)
    {
        default:
            break;
        case 1:
            DataCreateUI(startData, endData, dataNumber, backup, changeCounter);
            break;
        case 2:
            DataReadUI(startData, endData, *dataNumber);
            break;
        case 3:
            DataUpdateUI(startData, endData, *dataNumber, backup, changeCounter);
            break;
        case 4:
            DataDeleteUI(startData, endData, dataNumber, backup, changeCounter);
            break;
        case 5:
            if (*changeCounter == 0)
            {
                // quit
                operateCode = -1;
            }
            else
            {
                DataRedo(startData, endData, dataNumber, backup, changeCounter);
            }
            break;
        case 6:
            if (*changeCounter != 0)
            {
                SaveData(filePath, startData, endData);
            }
        case 7:
            if (*changeCounter != 0)
            {
                // quit
                operateCode = -1;
            }
            break;
    }

    return operateCode;
}