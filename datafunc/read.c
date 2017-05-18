/*
 * Data Function - Read
 * 
 * Author: Zhou Fang
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

/**
 * ╦═╗╔═╗╔═╗╔╦╗  ┬ ┬┬
 * ╠╦╝║╣ ╠═╣ ║║  │ ││
 * ╩╚═╚═╝╩ ╩═╩╝  └─┘┴
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/7/2017
 * Help user to find and display saved data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataNumber to display the number of data.
 */
void DataReadUI(data *startData, data *endData, int dataNumber)
{
    int dataID = 0;
    int isReturn = 1;

    dataID = FindID(startData, endData, dataNumber, "既存のデータの検索と表示");

    if (dataID != 0)
    {
        ClearScreen();
        ShowTitle();
        printf("==[%s]======================\n", "既存のデータの検索と表示");
        printf("\n= Result:\n");
        DataRead(startData, endData, dataID);
        printf("\n= 0 戻る\n>");
        FlushBuffer();
        scanf("%d", &isReturn);
        while (isReturn != 0) {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &isReturn);
        }
    }
}

/**
 * ╦═╗╔═╗╔═╗╔╦╗
 * ╠╦╝║╣ ╠═╣ ║║
 * ╩╚═╚═╝╩ ╩═╩╝
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Display the data by unique data ID.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataID the unique ID which is datum have.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataRead(data *startData, data *endData, int dataID)
{
    int resultCode = 0;
    data *tempData;

    for (tempData = startData; tempData != NULL; tempData = tempData->next) {
        if (tempData->id == dataID)
        {
            printf("%d|%s|%s|%s|%s\n", tempData->id, tempData->name,tempData->sex,tempData->mail,tempData->group);
            resultCode = 1;
            break;
        }
    }
    return resultCode;
}

/**
 * ╦═╗╔═╗╔═╗╔╦╗  ┌─┐┌┬┐┬┌┬┐┌─┐┌┬┐
 * ╠╦╝║╣ ╠═╣ ║║  ├┤  │││ │ ├┤  ││
 * ╩╚═╚═╝╩ ╩═╩╝  └─┘─┴┘┴ ┴ └─┘─┴┘
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/7/2017
 * Display the data by unique data ID.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {data*} editedData where the edited data.
 * @param {int} dataID the unique ID which is datum have.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataReadEdited(data *startData, data *endData, data *editedData, int dataID)
{
    int resultCode = 0;
    data *tempData;

    for (tempData = startData; tempData != NULL; tempData = tempData->next) {
        if (tempData->id == dataID)
        {
            printf("%5s   %-25s   %-25s\n", " ", "Original", "Edited");
            printf("%5s | %-25s | %-25s\n", "Name", tempData->name, editedData->name);
            printf("%5s | %-25s | %-25s\n", "Sex", tempData->sex, editedData->sex);
            printf("%5s | %-25s | %-25s\n", "Mail", tempData->mail, editedData->mail);
            printf("%5s | %-25s | %-25s\n", "Group", tempData->group, editedData->group);
            resultCode = 1;
            break;
        }
    }
    return resultCode;
}

/** OLD VERSION
 * ╦═╗╔═╗╔═╗╔╦╗  ┌─┐┬  ┬
 * ╠╦╝║╣ ╠═╣ ║║  ├─┤│  │
 * ╩╚═╚═╝╩ ╩═╩╝  ┴ ┴┴─┘┴─┘
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/8/2017
 * Display all data by A~Z.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataReadAllOld(data *startData, data *endData)
{
    int resultCode = 0;
    data *tempData;
    char firstLetter;

    for (firstLetter = 'A';  firstLetter <= 'Z' ; firstLetter++) {
        for (tempData = startData; tempData != NULL; tempData = tempData->next)
        {
            if (firstLetter == tempData->name[0] || (firstLetter + 32)  == tempData->name[0] )
            {
                printf("%d|%s|%s|%s|%s\n", tempData->id, tempData->name,tempData->sex,tempData->mail,tempData->group);
                resultCode = 1;
            }
        }
    }

    return resultCode;
}

/** NEW VERSION
 * ╦═╗╔═╗╔═╗╔╦╗  ┌─┐┬  ┬
 * ╠╦╝║╣ ╠═╣ ║║  ├─┤│  │
 * ╩╚═╚═╝╩ ╩═╩╝  ┴ ┴┴─┘┴─┘
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/18/2017
 * Display all data by A~Z.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataReadAll(data *startData, data *endData)
{
    simpledata *tempStart = (simpledata *)calloc(1, sizeof(simpledata));
    simpledata *tempEnd = tempStart;
    simpledata *loopPointer;
    simpledata *loopTempPointer;
    simpledata *smallestData;
    int loopIndex = 0;
    int dataSum = 0;// the number of data
    int tempId;
    char tempName[30];

    data *tempData;
    simpledata *tempSimpleData;

    tempData = startData;

    // copy all data to new list simply.
    for (; tempData != NULL; tempData = tempData->next)
    {
        tempEnd->id = tempData->id;
        strcpy(tempEnd->name, tempData->name);

        if (tempData->next != NULL)
        {
            tempEnd->next = (simpledata *)calloc(1, sizeof(simpledata));
            tempEnd = tempEnd->next;
        }
        else
        {
            tempEnd->next = NULL;
        }

        dataSum++;
    }

    loopPointer = tempStart;

    for (loopIndex = 0; loopIndex < dataSum; loopIndex++)
    {

        smallestData = loopPointer;

        // find smallest name
        for (loopTempPointer = loopPointer; loopTempPointer != NULL; loopTempPointer = loopTempPointer->next)
        {
            if (strcmp(loopTempPointer->name, smallestData->name) < 0)
            {
                smallestData = loopTempPointer;
            }
        }

        if (smallestData->id != loopPointer->id)
        {
            tempId = smallestData->id;
            smallestData->id = loopPointer->id;
            loopPointer->id = tempId;

            strcpy(tempName, smallestData->name);
            strcpy(smallestData->name, loopPointer->name);
            strcpy(loopPointer->name, tempName);
        }

        loopPointer = loopPointer->next;
    }

    for (loopPointer = tempStart; loopPointer != NULL; loopPointer = loopPointer->next)
    {
        DataRead(startData, endData, loopPointer->id);
    }


    while(tempStart != NULL)
    {
        tempSimpleData = tempStart;
        tempStart = tempStart->next;
        free(tempSimpleData);
    }

    return 1;
}