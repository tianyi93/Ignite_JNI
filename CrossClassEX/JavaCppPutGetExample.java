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

package org.apache.ignite.examples.datagrid;

import org.apache.ignite.Ignite;
import org.apache.ignite.IgniteCache;
import org.apache.ignite.IgniteException;
import org.apache.ignite.Ignition;
import org.apache.ignite.binary.BinaryBasicIdMapper;
import org.apache.ignite.binary.BinaryBasicNameMapper;
import org.apache.ignite.binary.BinaryWriter;
import org.apache.ignite.configuration.BinaryConfiguration;
import org.apache.ignite.configuration.IgniteConfiguration;
import org.apache.ignite.examples.ExampleNodeStartup;
import org.apache.ignite.internal.util.ClassCache;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * This example demonstrates very basic operations on cache, such as 'put' and 'get'.
 * <p>
 * Remote nodes should always be started with special configuration file which
 * enables P2P class loading: {@code 'ignite.{sh|bat} examples/config/example-ignite.xml'}.
 * <p>
 * Alternatively you can run {@link ExampleNodeStartup} in another JVM which will
 * start node with {@code examples/config/example-ignite.xml} configuration.
 */
public class JavaCppPutGetExample {

    public static void main(String[] args) throws IgniteException, InterruptedException {

        IgniteConfiguration igniteConfiguration = new IgniteConfiguration();
        BinaryConfiguration bCfg = new BinaryConfiguration();
        bCfg.setCompactFooter(false);
        bCfg.setNameMapper(new BinaryBasicNameMapper(true));
        bCfg.setIdMapper(new BinaryBasicIdMapper(true));
        bCfg.setClassNames(Collections.singleton("org.apache.ignite.examples.datagrid.CrossClass"));

        igniteConfiguration.setBinaryConfiguration(bCfg);
        Ignite ignite = Ignition.start(igniteConfiguration);

        IgniteCache<Integer, String> cache = ignite.getOrCreateCache("myCache");
        for (int i = 0; i < 10; ++i)
            cache.put(i,Integer.toString(i));

        IgniteCache<Integer, CrossClass> ClassCache = ignite.getOrCreateCache("ClassCache");
        for (int i = 0; i < 10; ++i) {
            CrossClass item = new CrossClass(i,i);
            ClassCache.put(i, item);
        }

        Thread.sleep(1000000);
    }
}

