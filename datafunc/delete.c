/*
 * Data Function - Delete
 * 
 * Author: Yuto Takebayashi
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
 * ╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗  ┬ ┬┬
 *  ║║║╣ ║  ║╣  ║ ║╣   │ ││
 * ═╩╝╚═╝╩═╝╚═╝ ╩ ╚═╝  └─┘┴
 * Author: Yuto Takebayashi
 * Last Update: Zhou Fang @ 5/18/2017
 * Help user to find and delete saved data.
 * @param {data**} startData where the data start.
 * @param {data**} endData where the data end.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataDeleteUI(data **startData, data **endData, int *dataNumber, backupdata *backupData, int *changeCounter)
{
    int dataID = 0;
    int exitCode = 0;
    data *editedData;
    dataID = FindID(*startData, *endData, *dataNumber, "既存のデータのDelete");

    editedData = (data *)calloc(1, sizeof(data));

    if (dataID != 0)
    {
        do{
            ClearScreen();
            ShowTitle();
            printf("==[%s]======================\n", "既存のデータのDelete");
            printf("\n= Data: [Now]\n");
            DataRead(*startData, *endData, dataID);
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
 * Last Update: Zhou Fang @ 5/18/2017
 * Delete the data.
 * @param {data**} startData where the data start.
 * @param {data**} endData where the data end.
 * @param {int} dataID the unique ID which is datum have.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataDelete(data **startData, data **endData, int dataID, int *dataNumber, backupdata *backupData)
{
    data *tempDataBefore = *startData;
    data *tempData;


    if (dataID == (*startData)->id)
    {
        tempData = (*startData);
        (*startData) = (*startData)->next;

        backupData->operationCode = 1;
        backupData->id = dataID;
        strcpy(backupData->name, tempData->name);
        strcpy(backupData->mail, tempData->mail);
        strcpy(backupData->sex, tempData->sex);
        strcpy(backupData->group, tempData->group);

        free(tempData);
    }
    else
    {
        for (tempData = (*startData); tempData != NULL; tempData = tempData->next) {

            if (tempData->id == dataID) {

                backupData->operationCode = 1;
                backupData->id = dataID;
                strcpy(backupData->name, tempData->name);
                strcpy(backupData->mail, tempData->mail);
                strcpy(backupData->sex, tempData->sex);
                strcpy(backupData->group, tempData->group);

                tempDataBefore->next = tempData->next;
                free(tempData);
                break;
            }

            tempDataBefore = tempData;
        }
    }

    (*dataNumber)--;
    return 1;
}