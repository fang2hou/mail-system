/*
 * Basic Functions
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

#include <stdlib.h>
#include <string.h>

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 4/24/2017
 * Fix the input problem by flush the buffer.
 */
void FlushBuffer()
{
    setbuf(stdin, NULL);
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Fix the fgets problem by removing the last '\n'.
 * @param {char*} string The string that will be change.
 */
void StringInLine(char *string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/7/2017
 * Auto flush buffer and get input from stdin.
 * @param {char*} string The string that will be change.
 * @param {int} length The max length.
 */
void GetString(char *string, int length)
{
    FlushBuffer();
    fgets(string, length, stdin);
    StringInLine(string);
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 4/24/2017
 * Clear the screen (multi-platform support)
 */
void ClearScreen()
{
    // identify platform
    #ifdef _WIN32 // for Windows
        system("cls");
    #else // for *nix based system
        system("clear");
    #endif
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/7/2017
 * Close a file by pointer.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @return {int} Success -> 1, Failed -> 0.
 */
int FreeData(data *startData, data *endData)
{
    data *tempData;

    while(startData != NULL)
    {
        tempData = startData;
        startData = startData->next;
        free(tempData);
    }

    return 1;
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 4/24/2017
 * Display the title of the program.
 */
void ShowTitle()
{
    printf("\n"
                   "___  ___ ___ _____ _       _______   _______ _____ ________  ___\n"
                   "|  \\/  |/ _ \\_   _| |     /  ___\\ \\ / /  ___|_   _|  ___|  \\/  |\n"
                   "| .  . / /_\\ \\| | | |     \\ `--. \\ V /\\ `--.  | | | |__ | .  . |\n"
                   "| |\\/| |  _  || | | |      `--. \\ \\ /  `--. \\ | | |  __|| |\\/| |\n"
                   "| |  | | | | || |_| |____ /\\__/ / | | /\\__/ / | | | |___| |  | |\n"
                   "\\_|  |_|_| |_|___/\\_____/ \\____/  \\_/ \\____/  \\_/ \\____/\\_|  |_/\n"
                   "\n\n");


    // Previous version
    //printf("////////////////////////////////////////\n");
    //printf("///        Mail Address System       ///\n");
    //printf("///            by Group F            ///\n");
    //printf("////////////////////////////////////////\n");
}

/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 4/24/2017
 * Display the main menu.
 * @param {int} changeCounter display the hidden menu after changing.
 */
void ShowMain(int changeCounter)
{
    printf("==[メインメニュー]======================\n");
    printf("= 1 新しいデータの追加\n");
    printf("= 2 データの表示\n");
    printf("= 3 既存データの更新\n");
    printf("= 4 既存データの消去\n");
    if (changeCounter != 0)
    {
        printf("= 5 操作を取り消す\n");
        printf("= 6 保存＆終了\n");
        printf("= 7 保存しないで終了\n");
    }
    else
    {
        printf("= 5 終了\n");
    }
}


/**
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/7/2017
 * Save data to file.
 * @param {char*} filePath The path of data file.
 * @param {data**} startData where the data start.
 * @param {data**} endData where the data end.
 * @param {int*} dataNumber The number of data.
 * @return {int} Success -> 1, Failed -> 0.
 */
int LoadData(char *filePath, data **startData, data **endData, int *dataNumber)
{
    int resultCode = 0;
    FILE *file = fopen(filePath, "r");

    data tempData;
    char tempString[300];
    char *tempSplitedString;

    if (file == NULL)
    {
        printf("残念ですが、CSVファイルの読み込みに問題が発生した。\n");
    }
    else {
        // Set data to struct
        fgets(tempString, 300, file);
        StringInLine(tempString);
        *startData = (data *)calloc(1, sizeof(data));
        *endData = *startData;

        for ((*dataNumber) = 0; fgets(tempString, 300, file) != NULL; (*dataNumber)++) {
            // split the one-line data and set to tempData
            tempSplitedString = strtok(tempString, ",");
            tempData.id = atoi(tempSplitedString);
            tempSplitedString = strtok(NULL, ",");
            strcpy(tempData.name, tempSplitedString);
            tempSplitedString = strtok(NULL, ",");
            strcpy(tempData.sex, tempSplitedString);
            tempSplitedString = strtok(NULL, ",");
            strcpy(tempData.mail, tempSplitedString);
            tempSplitedString = strtok(NULL, ",");
            // fix the bug which will save the '\n' in last string
            StringInLine(tempSplitedString);
            strcpy(tempData.group, tempSplitedString);

            tempData.next = NULL;
            if ((*dataNumber) >= 1) {
                (*endData)->next = (data *)calloc(1, sizeof(data));
                (*endData) = (*endData)->next;
            }
            **endData = tempData;
        }
        resultCode = 1;
    }

    fclose(file);
    return resultCode;
}

/**
 * Author: Ryosuke Ukita
 * Last Update: Zhou Fang @ 5/7/2017
 * Save data to file.
 * @param {char*} filePath The path of data file.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 */
int SaveData(char *filePath,data *startData, data *endData)
{
    FILE *CSVFile;
    data *data;
    data = startData;

    CSVFile = fopen(filePath,"w");

    fprintf(CSVFile,"#Id,Name,Sex,Mail address,Group");

    while (data != NULL)
    {
        fprintf(CSVFile,"\n%d,%s,%s,%s,%s", data -> id, data -> name, data -> sex, data -> mail, data -> group);
        data = data -> next;
    }

    fclose(CSVFile);

    return 1;
}