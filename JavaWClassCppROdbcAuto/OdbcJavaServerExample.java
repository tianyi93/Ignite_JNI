package org.apache.ignite.examples.datagrid;

import org.apache.ignite.Ignite;
import org.apache.ignite.IgniteCache;
import org.apache.ignite.IgniteException;
import org.apache.ignite.Ignition;
import org.apache.ignite.cache.QueryEntity;
import org.apache.ignite.cache.QueryIndex;
import org.apache.ignite.cache.query.QueryCursor;
import org.apache.ignite.cache.query.SqlFieldsQuery;
import org.apache.ignite.configuration.CacheConfiguration;
import org.apache.ignite.examples.model.Person;
import org.apache.ignite.binary.BinaryBasicIdMapper;
import org.apache.ignite.binary.BinaryBasicNameMapper;
import org.apache.ignite.configuration.BinaryConfiguration;
import org.apache.ignite.configuration.IgniteConfiguration;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;


public class OdbcJavaServerExample {

    public static void main(String[] args) throws IgniteException, InterruptedException, Exception  {
	
//binary configuration needed as c++ node and java node are communicating
        IgniteConfiguration igniteConfiguration = new IgniteConfiguration();
        BinaryConfiguration bCfg = new BinaryConfiguration();
        bCfg.setCompactFooter(false);
        bCfg.setNameMapper(new BinaryBasicNameMapper(true));
        bCfg.setIdMapper(new BinaryBasicIdMapper(true));
        igniteConfiguration.setBinaryConfiguration(bCfg);

        CacheConfiguration cacheCfg = new CacheConfiguration("Person");
        cacheCfg.setIndexedTypes(java.lang.Long.class, Person.class);
        igniteConfiguration.setCacheConfiguration(cacheCfg);

        Ignite ignite = Ignition.start(igniteConfiguration);
        IgniteCache cache = ignite.getOrCreateCache("Person");

        Person p = new Person((long)1,"Joe", "Doe from java");
        Person p0 = new Person((long)2,"M", "2 from java");
        p.resume = "ms";
        p.salary = 2000;
        Long index =1L;
        cache.put(index,p);
        cache.put(0L, p0);
    }
}