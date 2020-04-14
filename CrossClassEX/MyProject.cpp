/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <windows.h>

#include "ignite/ignite.h"
#include "ignite/ignition.h"

#include "ignite/examples/organization.h"
#include "CrossClass.h"

using namespace ignite;
using namespace cache;

using namespace examples;

int main()
{
    IgniteConfiguration cfg;
    cfg.springCfgPath = "C:/Users/harte/Desktop/work/apache-ignite-2.8.0-bin/platforms/cpp/examples/project/vs/myProject/CrossClassConf.xml";
    try {
        Ignite grid = Ignition::Start(cfg);

        Cache<int, std::string> cache = grid.GetCache<int, std::string>("myCache");
        Cache<int, ignite::binary::CrossClass> Classcache = grid.GetCache<int, ignite::binary::CrossClass>("ClassCache");

        std::cout << "```````````````````Getting key, string pair``````````````````````````````" << std::endl;
        for (int i = 0; i < 10; ++i)
            std::cout << "Got [key=" << i << ", val=" << cache.Get(i) << "]"<<std::endl;

        std::cout << "```````````````````Getting key, CrossClass pair``````````````````````````````" << std::endl;
        for (int i = 0; i < 10; ++i)
            std::cout << "Got [key=" << i << ", id=" << Classcache.Get(i).id << ", idPart" << Classcache.Get(i).idPart << "]" << std::endl;
    }
    catch (IgniteError & err)
    {
        std::cout << "An error occurred: " << err.GetText() << std::endl;

        return err.GetCode();
    }
    return 0;
}
