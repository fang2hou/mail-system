/*
 * Data Function - Create
 * 
 * Author: Tatsuya Kawamura
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
 * ╔═╗╦═╗╔═╗╔═╗╔╦╗╔═╗  ┬ ┬┬
 * ║  ╠╦╝║╣ ╠═╣ ║ ║╣   │ ││
 * ╚═╝╩╚═╚═╝╩ ╩ ╩ ╚═╝  └─┘┴
 * Author: Tatsuya Kawamura
 * Last Update: Zhou Fang @ 5/18/2017
 * Help user to input the information and store data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int*} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataCreateUI(data **startData, data **endData, int *dataNumber, backupdata *backupData, int *changeCounter)
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

    if( DataCreate(startData, endData, newData, dataNumber, backupData, 1) == 1 )
    {
        (*changeCounter)++;
    }
}

/**
 * ╔═╗╦═╗╔═╗╔═╗╔╦╗╔═╗
 * ║  ╠╦╝║╣ ╠═╣ ║ ║╣
 * ╚═╝╩╚═╚═╝╩ ╩ ╩ ╚═╝
 * Author: Tatsuya Kawamura
 * Last Update: Zhou Fang @ 5/18/2017
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

        if (dataID < (*startData)->id)
        {
            newData->next = (*startData);
            (*startData) = newData;
        }
        else
        {
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
        }


        (*dataNumber)++;
        return 1;
    }
}