	Drop DATABASE if exists PlayerBase;
    CREATE DATABASE PlayerBase;
    USE PlayerBase;
    
    CREATE TABLE Player (
		username VARCHAR(20) primary key not null,
        password VARCHAR(20) not null,
		levelcompleted int(10) not null
    );
    
    INSERT INTO Player (username, password, levelcompleted) VALUES ('johnny', 'karate', 2);
    INSERT INTO Player (username, password, levelcompleted) VALUES ('me', 'me', 1);
    
    
	