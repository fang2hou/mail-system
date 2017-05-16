/*
 * Data Control Functions
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
 * ╔═╗╦═╗╔═╗╔═╗╔╦╗╔═╗  ┬ ┬┬
 * ║  ╠╦╝║╣ ╠═╣ ║ ║╣   │ ││
 * ╚═╝╩╚═╚═╝╩ ╩ ╩ ╚═╝  └─┘┴
 * Author: Tatsuya Kawamura
 * Last Update: Zhou Fang @ 5/7/2017
 * Help user to input the information and store data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataCreateUI(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter)
{
    data *newData;

    // get new memory space to store data
    newData = (data *) calloc(1, sizeof(data));

    printf("追加したいデータを入力してください.\n");

    printf("1 名前：");
    GetString(newData->name, 30);

    printf("2 メール：");
    GetString(newData->mail, 30);

    printf("3 性別：");
    GetString(newData->sex, 30);

    printf("4 グループ：");
    GetString(newData->group, 30);

    if( DataCreate(&startData, &endData, newData, dataNumber, backupData, 1) == 1 )
    {
        (*changeCounter)++;
    }
}

/**
 * ╔═╗╦═╗╔═╗╔═╗╔╦╗╔═╗
 * ║  ╠╦╝║╣ ╠═╣ ║ ║╣
 * ╚═╝╩╚═╚═╝╩ ╩ ╩ ╚═╝
 * Author: Tatsuya Kawamura
 * Last Update: Zhou Fang @ 5/7/2017
 * Create the data.
 * @param {data**} startData where the data start.
 * @param {data**} endData where the data end.
 * @param {data*} newData where the data will be added.
 * @param {int} dataID the unique ID which is datum have.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int} mode The mode code given by user.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataCreate(data **startData, data **endData, data *newData, int *dataNumber, backupdata *backupData, int mode)
{
    int dataID = 0;
    int dataIDBefore = 0;

    data *tempData;
    data *dataBefore = *endData;


    if (mode == 1)
    {
        // generate new id
        dataID = (*endData)->id;
        dataID++;

        // rewrite the id of new data
        newData->id = dataID;
        newData->next = NULL;

        (*endData)->next = newData;
        (*endData) = (*endData)->next;
        (*dataNumber)++;

        // check the new data and return
        if ((*endData)->id == dataID)
        {
            // set redo info
            backupData->operationCode = 3;
            backupData->id = dataID;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        dataID = newData->id;

        for (tempData = *startData; tempData != NULL; tempData = tempData->next)
        {
            if (dataIDBefore < dataID && dataID < tempData->id)
            {
                break;
            }

            dataBefore = tempData;
            dataIDBefore = tempData->id;
        }

        newData->next = tempData;
        dataBefore->next = newData;
        (*dataNumber)++;
        return 1;
    }
}

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

/**
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
int DataReadAll(data *startData, data *endData)
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


/**
 * ╦ ╦╔═╗╔╦╗╔═╗╔╦╗╔═╗  ┬ ┬┬
 * ║ ║╠═╝ ║║╠═╣ ║ ║╣   │ ││
 * ╚═╝╩  ═╩╝╩ ╩ ╩ ╚═╝  └─┘┴
 * Author: Atsushi Hasegawa
 * Last Update: Zhou Fang @ 5/7/2017
 * Help user to find and update saved data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataUpdateUI(data *startData, data *endData, int dataNumber, backupdata *backupData, int *changeCounter)
{
    int dataID = 0;
    int exitCode = 0;
    data *editedData;
    dataID = FindID(startData, endData, dataNumber, "既存のデータのUPDATE");

    editedData = (data *)calloc(1, sizeof(data));

    if (dataID != 0)
    {
        do{
            ClearScreen();
            ShowTitle();
            printf("==[%s]======================\n", "既存のデータのUPDATE");
            DataReadEdited(startData, endData, editedData, dataID);
            printf("===================================\n");
            printf("= 1 名前の変更\n");
            printf("= 2 メールアドレスの変更\n");
            printf("= 3 性別の変更\n");
            printf("= 4 グループの変更\n");
            printf("= 5 保存\n");
            printf("= 0 終了\n>");
            FlushBuffer();
            scanf("%d", &exitCode);
            switch (exitCode){
                default:
                    printf("入力したモードは存在しません、もう一度入力してください。\n");
                    break;
                case 0:
                    break;
                case 1:
                    printf("New name: ");
                    GetString(editedData->name, 30);
                    break;
                case 2:
                    printf("New mail: ");
                    GetString(editedData->mail, 30);
                    break;
                case 3:
                    printf("New sex: ");
                    GetString(editedData->sex, 30);
                    break;
                case 4:
                    printf("New group: ");
                    GetString(editedData->group, 30);
                    break;
                case 5:
                    if( DataUpdate(startData, endData, editedData, dataID, backupData) == 1 )
                    {
                        (*changeCounter)++;
                    }
                    exitCode = 0;
                    break;
            }
        } while (exitCode != 0);
    }

    free(editedData);
}

/**
 * ╦ ╦╔═╗╔╦╗╔═╗╔╦╗╔═╗
 * ║ ║╠═╝ ║║╠═╣ ║ ║╣
 * ╚═╝╩  ═╩╝╩ ╩ ╩ ╚═╝
 * Author: Atsushi Hasegawa
 * Last Update: Zhou Fang @ 5/7/2017
 * update data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {data*} editedData where the edited data is.
 * @param {int} dataID the unique ID which is datum have.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataUpdate(data *startData, data *endData, data *editedData, int dataID, backupdata *backupData)
{
    data *tempData;
    backupdata *tempBackupData;
    tempBackupData = (backupdata *)calloc(1, sizeof(backupdata));
    tempBackupData->id = dataID;

    for (tempData = startData; tempData != NULL; tempData = tempData->next) {
        if (tempData->id == dataID) {
            if (strlen(editedData->name) != 0)
            {
                strcpy(tempBackupData->name, tempData->name);
                strcpy(tempData->name, editedData->name);
            }

            if (strlen(editedData->mail) != 0)
            {
                strcpy(tempBackupData->mail, tempData->mail);
                strcpy(tempData->mail, editedData->mail);
            }
            if (strlen(editedData->sex) != 0)
            {
                strcpy(tempBackupData->sex, tempData->sex);
                strcpy(tempData->sex, editedData->sex);
            }

            if (strlen(editedData->group) != 0)
            {
                strcpy(tempBackupData->group, tempData->group);
                strcpy(tempData->group, editedData->group);
            }

            break;
        }
    }

    free(backupData);
    backupData = tempBackupData;

    return  1;
}

/**
 * ╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗  ┬ ┬┬
 *  ║║║╣ ║  ║╣  ║ ║╣   │ ││
 * ═╩╝╚═╝╩═╝╚═╝ ╩ ╚═╝  └─┘┴
 * Author: Yuto Takebayashi
 * Last Update: Zhou Fang @ 5/7/2017
 * Help user to find and delete saved data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataDeleteUI(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter)
{
    int dataID = 0;
    int exitCode = 0;
    data *editedData;
    dataID = FindID(startData, endData, *dataNumber, "既存のデータのDelete");

    editedData = (data *)calloc(1, sizeof(data));

    if (dataID != 0)
    {
        do{
            ClearScreen();
            ShowTitle();
            printf("==[%s]======================\n", "既存のデータのDelete");
            printf("\n= Data: [Now]\n");
            DataRead(startData, endData, dataID);
            printf("===================================");
            printf("\n= 1 消去\n");
            printf("= 0 終了\n>");
            FlushBuffer();
            scanf("%d", &exitCode);
            switch (exitCode){
                default:
                    printf("入力したモードは存在しません、もう一度入力してください。\n");
                    break;
                case 0:
                    break;
                case 1:
                    if (DataDelete(startData, endData, dataID, dataNumber, backupData) == 1)
                    {
                        (*changeCounter)++;
                    }
                    exitCode = 0;
                    break;
            }
        } while (exitCode != 0);
    }

    free(editedData);
}

/**
 * ╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗
 *  ║║║╣ ║  ║╣  ║ ║╣
 * ═╩╝╚═╝╩═╝╚═╝ ╩ ╚═╝
 * Author: Yuto Takebayashi
 * Last Update: Zhou Fang @ 5/7/2017
 * Delete the data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataID the unique ID which is datum have.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataDelete(data *startData, data *endData, int dataID, int *dataNumber, backupdata *backupData)
{
    data *tempDataBefore = startData;
    data *tempData;

    for (tempData = startData; tempData != NULL; tempData = tempData->next) {

        if (tempData->id == dataID) {

            backupData->operationCode = 1;
            backupData->id = dataID;
            strcpy(backupData->name, tempData->name);
            strcpy(backupData->mail, tempData->mail);
            strcpy(backupData->sex, tempData->sex);
            strcpy(backupData->group, tempData->group);

            tempDataBefore->next = tempData->next;
            free(tempData);
            (*dataNumber)--;
            break;
        }

        tempDataBefore = tempData;
    }
    return 1;
}

/**
 * ╔═╗╦╔╗╔╔╦╗  ┬┌┬┐
 * ╠╣ ║║║║ ║║  │ ││
 * ╚  ╩╝╚╝═╩╝  ┴─┴┘
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Use 3 methods to find the unique id.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataNumber to display the number of data.
 * @param {char*} subTitle the sub title which will be displayed.
 * @return {int} operateCode no found -> 0, found -> else.
 */
int FindID(data *startData, data *endData, int dataNumber, char *subTitle)
{
    int loopIndex = 0;
    int searchMode = 0;// 1-Name 2-Mail 3-Group
    int resultCounter = 0;
    int isMatch = 0;
    int result = 0;
    data *tempStartData;
    data *tempEndData;
    data *currentData;
    char keyword[50];

    //init
    tempEndData = malloc(sizeof(data));
    tempStartData = tempEndData;

    currentData = startData;
    ClearScreen();
    ShowTitle();
    printf("==[%s]=======================\n", subTitle);
    printf("= 今のデータ数：%d\n", dataNumber);
    printf("= 1 名前で検索\n");
    printf("= 2 メールアドレスで検索\n");
    printf("= 3 グループで検索\n");
    printf("= 4 すべてのデータを表示（A〜Z順）\n");
    printf("= 0 戻る\n>");

    FlushBuffer();
    scanf("%d", &searchMode);

    // make sure the correct mode code has been inputted
    while (searchMode < -1 || searchMode > 4) {
        printf("入力したモードは存在しません、もう一度入力してください。\n");
        FlushBuffer();
        scanf("%d", &searchMode);
    }

    // if the mode code is 0, quit immediately
    if (searchMode == 0)
    {
        return 0;
    }
    else if(searchMode == 4)
    {
        ClearScreen();
        ShowTitle();
        printf("==[%s]=======================\n", subTitle);
        DataReadAll(startData, endData);
        printf("\n= 0 戻る\n>");

        FlushBuffer();
        scanf("%d", &searchMode);

        while (searchMode != 0)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
        result = FindID(startData, endData, dataNumber, subTitle);
        return result;
    }
    printf("\nキーワードを入力してください\n>");

    // get the keyword (length < 128)
    FlushBuffer();
    fgets(keyword, 128, stdin);
    StringInLine(keyword);

    ClearScreen();
    ShowTitle();
    printf("==[%s]======================\n", subTitle);

    for (loopIndex = 0; loopIndex < dataNumber; currentData = currentData->next)
    {
        isMatch = 0;

        loopIndex++;

        switch(searchMode)
        {
            default:
                break;
            case 1:
                if (strstr(currentData->name, keyword))
                {
                    isMatch = 1;
                }
                break;
            case 2:
                if (strstr(currentData->mail, keyword))
                {
                    isMatch = 1;
                }
                break;
            case 3:
                if (strstr(currentData->group, keyword))
                {
                    isMatch = 1;
                }
                break;
        }

        if (isMatch == 1)
        {

            if (resultCounter > 0)
            {
                tempEndData->next = malloc(sizeof(data));
                tempEndData = tempEndData->next;
            }
            *tempEndData = *currentData;
            tempEndData->next = NULL;
            resultCounter++;
            DataRead(startData, endData, currentData->id);
        }
    }

    // if there is just one datum has been found, let user lock the result.
    printf("\n= 結果数：%d\n", resultCounter);
    if (resultCounter == 1)
    {
        printf("= 1 確定\n");
    }
    else if (resultCounter > 1)
    {
        printf("= 1 他のキーワードでデータを特定\n");
    }
    printf("= 8 A~Zで表示\n");
    printf("= 9 他のキーワードで絞り込む\n");
    printf("= 0 戻る\n>");

    // get modecode from standard input
    FlushBuffer();
    scanf("%d", &searchMode);

    // make sure the mode code
    if (resultCounter == 0)
    {
        while (searchMode != 9 && searchMode != 0 && searchMode != 8)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
    }
    else if (resultCounter >= 1)
    {
        while (searchMode != 1 && searchMode != 9 && searchMode != 0 && searchMode != 8)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
    }

    // return the unique id or call FindID one more time
    switch (searchMode)
    {
        default:
            break;
        case 1:
            if (resultCounter == 1)
            {
                result = tempEndData->id;
            }
            else
            {
                result = FindID(tempStartData, tempEndData, resultCounter, subTitle);
            }
            break;
        case 8:
            DataReadAll(tempStartData, tempEndData);
            printf("\n= 0 戻る\n>");
            FlushBuffer();
            scanf("%d", &searchMode);

            while (searchMode != 0)
            {
                FlushBuffer();
                scanf("%d", &searchMode);
            }
            result = 0;
            break;
        case 9:
            result = FindID(startData, endData, dataNumber, subTitle);
            break;
        case 0:
            result = 0;
            break;
    }

    FreeData(tempStartData, tempEndData);
    return result;
}

/**
 * ╦═╗╔═╗╔╦╗╔═╗
 * ╠╦╝║╣  ║║║ ║
 * ╩╚═╚═╝═╩╝╚═╝
 * Author: Masuda Tatsuki
 * Last Update: Zhou Fang @ 5/1/2017
 * Redo function.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int*} dataNumber to display the number of data.]
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataRedo(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter)
{
    int resultCode = 0;
    data *tempData;

    (*changeCounter)--;

    tempData = (data *)calloc(1, sizeof(data));
    tempData->id = backupData->id;
    strcpy(tempData->name, backupData->name);
    strcpy(tempData->mail, backupData->mail);
    strcpy(tempData->sex, backupData->sex);
    strcpy(tempData->group, backupData->group);

    switch(backupData->operationCode)
    {

        case 1: // Deleted
            DataCreate(&startData, &endData, tempData, dataNumber, backupData, 2);
            break;
        case 2: // Edited
            DataUpdate(startData, endData, tempData, backupData->id, backupData);
            free(tempData);
            break;
        case 3: // Created
            DataDelete(startData, endData, backupData->id, dataNumber, backupData);
            free(tempData);
            break;
        default:
            free(tempData);
            break;
    }

    return resultCode;
}