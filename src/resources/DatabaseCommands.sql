
-- ---
-- Globals
-- ---

-- SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
-- SET FOREIGN_KEY_CHECKS=0;

-- ---
-- Table 'member'
-- 
-- ---

DROP TABLE IF EXISTS `member`;
        
CREATE TABLE `member` (
  `id` INTEGER NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`id`)
);

-- ---
-- Table 'expense'
-- 
-- ---

DROP TABLE IF EXISTS `expense`;
        
CREATE TABLE `expense` (
  `id` INTEGER NOT NULL AUTO_INCREMENT,
  `type` ENUM ('veg', 'non_veg') NOT NULL,
  `date` DATETIME NOT NULL,
  `expense` DOUBLE NOT NULL,
  `description` MEDIUMINT NOT NULL,
  PRIMARY KEY (`id`)
);

-- ---
-- Table 'daily_records'
-- 
-- ---

DROP TABLE IF EXISTS `daily_records`;
        
CREATE TABLE `daily_records` (
  `id` INTEGER NOT NULL AUTO_INCREMENT,
  `date` DATETIME NOT NULL,
  `member_id` INTEGER NOT NULL,
  `session` ENUM ('break_fast', 'lunch', 'dinner') NOT NULL,
  `category` ENUM ('veg', 'non_veg') NOT NULL,
  PRIMARY KEY (`id`)
);

-- ---
-- Foreign Keys 
-- ---


-- ---
-- Table Properties
-- ---

-- ALTER TABLE `member` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `expense` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `daily_records` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ---
-- Test Data
-- ---

-- INSERT INTO `member` (`id`,`name`) VALUES
-- ('','');
-- INSERT INTO `expense` (`id`,`type`,`date`,`expense`,`description`) VALUES
-- ('','','','','');
-- INSERT INTO `daily_records` (`id`,`date`,`member_id`,`session`,`category`) VALUES
-- ('','','','','');
