package org.apache.ignite.examples.datagrid;

import org.apache.ignite.Ignite;
import org.apache.ignite.IgniteCache;
import org.apache.ignite.IgniteException;
import org.apache.ignite.Ignition;
import org.apache.ignite.examples.model.Person;
import org.apache.ignite.binary.BinaryBasicIdMapper;
import org.apache.ignite.binary.BinaryBasicNameMapper;
import org.apache.ignite.configuration.BinaryConfiguration;
import org.apache.ignite.configuration.IgniteConfiguration;

import java.util.Collections;

public class OdbcJavaServerExample {
    public static void main(String[] args) throws IgniteException, InterruptedException {
        Ignite ignite = Ignition.start("C:/Users/harte/Desktop/work/apache-ignite-2.8.0-bin/platforms/cpp/examples/odbc-example/config/example-odbc.xml");
        Person p = new Person((long)1,"Joe", "Doe from java");
        IgniteCache<Long, Person> cacheperson = ignite.cache("Person");
        Long index =1L;
        cacheperson.put(index,p);


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
