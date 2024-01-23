-- 공통프로젝트 PoopKey DATABASE --
-- ver1.1.1
-- 수정사항 : 모든 테이블의 PK에 auto_increment 직접추가
-- ver1.1.2
-- 수정사항 : item 테이블의 tissue_status column 제거(SQL에서 계산되므로 불필요함)
-- ver1.1.3
-- 수정사항 : user 테이블의 비밀번호, 이메일 NOT NULL로 바꿈
DROP SCHEMA IF EXISTS `poopkey` ;

-- -----------------------------------------------------
-- Schema poopkey
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `poopkey` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `poopkey` ;

CREATE TABLE `master` (
	`master_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`password`	varchar(255)	NOT NULL	COMMENT 'hash한 결과값을 저장해야 한다.',
	`name`	varchar(100)	NOT NULL,
	`phone`	varchar(20)	NULL,
	`device_id`	varchar(255)	NOT NULL,
	`created_date`	timestamp	NOT NULL,
	`email`	varchar(255)	NOT NULL	COMMENT '이메일 주소가 아이디 역할',
	`profile`	longblob	NULL	COMMENT '이미지파일을 binary형태로 DB에 저장, 기본이미지 파일 준비하기',
	`address`	varchar(255)	NULL
);

CREATE TABLE `restroom` (
	`restroom_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`building_id`	bigint(20)	NOT NULL,
	`floor`	int(3)	NOT NULL	DEFAULT 1,
	`congestion`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 원활
1 : 혼잡
2 : 포화',
	`gender`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0:남성, 1:여성',
	`cleaning`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0:청소x 1:청소중',
	`height`	int	NOT NULL	DEFAULT 1	COMMENT '인덱스 번호 1부터 시작',
	`width`	int	NOT NULL	DEFAULT 1	COMMENT '인덱스 번호 1부터 시작',
	`last_cleaning_time`	timestamp	NOT NULL
);

CREATE TABLE `building` (
	`building_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`master_id`	bigint(20)	NOT NULL,
	`building_name`	varchar(255)	NOT NULL,
	`building_lat`	double	NULL,
	`building_lng`	double	NULL,
	`congestion`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 원활1 : 혼잡2 : 포화',
	`address`	varchar(255)	NOT NULL	DEFAULT '서울특별시 강남구'
);
CREATE TABLE `report` (
	`report_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`stall_id`	bigint(20)	NOT NULL,
	`restroom_id`	bigint(20)	NOT NULL,
	`content`	varchar(255)	NULL,
	`created_date`	timestamp	NOT NULL,
	`user_report_reason`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '위생 : 0 파손 : 1기타 : 2  셋 중 하나를 선택'
);
CREATE TABLE `stall` (
	`stall_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`restroom_id`	bigint(20)	NOT NULL,
	`block_id`	bigint(20)	NOT NULL,
	`status`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '사용가능 : 0사용중 : 1고장 : 2점검 : 3고장의심 : 4',
	`last_used_time`	timestamp	NOT NULL	COMMENT '화장실을 사용했을 때 갱신',
	`closed`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 열림 1 : 잠김',
	`able`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 사용가능 1 : 사용불가',
	`used_number_after_cleaning`	int	NOT NULL	DEFAULT 0	COMMENT '청소 후 0 으로 reset',
	`used_number`	int	NOT NULL	DEFAULT 0,
	`break_number`	int	NOT NULL	DEFAULT 0,
	`cleaning`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 청소x  1 : 청소중',
	`stall_number`	int	NOT NULL	DEFAULT 1	COMMENT '1부터 시작하는 화장실 번호'
);

CREATE TABLE `toilet` (
	`toilet_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`stall_id`	bigint(20)	NOT NULL,
	`status`	tinyint(1)	NULL	COMMENT '변기 막힘 여부는 화장실 칸 table의 고장 column으로 반영된다.'
);

CREATE TABLE `item` (
	`item_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`stall_id`	bigint(20)	NOT NULL,
	`tissue`	int(3)	NOT NULL	DEFAULT 0	COMMENT '0부터 100까지 정수로 퍼센트 표시',
	`tissue_change_number`	int	NOT NULL	DEFAULT 0
);

CREATE TABLE `block` (
	`block_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`restroom_id`	bigint(20)	NOT NULL,
	`row`	int	NOT NULL	DEFAULT 1	COMMENT '인덱스 번호 1부터 시작',
	`col`	int	NOT NULL	DEFAULT 1	COMMENT '인덱스 번호 1부터 시작',
	`content`	tinyint(1)	NOT NULL	DEFAULT 0	COMMENT '0 : 빈칸1 : 화장실2 : 입구'
);
CREATE TABLE `user` (
	`user_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`password`	varchar(255)	NOT NULL,
	`email`	varchar(255)	NOT NULL	COMMENT '이메일 주소가 아이디 역할',
	`phone`	varchar(20)	NULL,
	`created_date`	timestamp	NOT NULL,
	`name`	varchar(100)	NOT NULL,
	`profile`	longblob  NULL	COMMENT '이미지파일을 binary 형태로 DB에 저장, 기본 이미지 파일 준비하기',
	`address`	varchar(255)	NULL
);

CREATE TABLE `bookmark` (
	`bookmark_id`	bigint(20)	NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`user_id`	bigint(20)	NOT NULL,
	`created_date`	timestamp	NOT NULL,
	`content`	varchar(255)	NOT NULL
);

-- DEBUGGING
SELECT * FROM user;
SELECT * FROM master;
SELECT * FROM building;
SELECT * FROM restroom;
SELECT * FROM block;
SELECT * FROM toilet;
SELECT * FROM report;
-- DUMMY DATA
INSERT INTO master VALUES
(1, '1234', '김싸피', '010-1234-5678', 'XYZ1234', CURRENT_TIMESTAMP, 'ssafy@ssafy.com',
NULL, '서울시 강남구 테헤란로 212');
INSERT INTO building VALUES
(1, 1, 'SSAFY 서울 캠퍼스', 37.5012851921, 127.0396046633, 0, '서울시 강남구 테헤란로 212');
INSERT INTO restroom VALUES
(1, 1, 1, 0, 0, 0, 3, 3, CURRENT_TIMESTAMP), -- SSAFY빌딩 1층 남자화장실
(2, 1, 1, 1, 1, 0, 3, 3, CURRENT_TIMESTAMP), -- SSAFY빌딩 1층 여자화장실
(3, 1, 2, 0, 0, 0, 3, 3, CURRENT_TIMESTAMP), -- SSAFY빌딩 2층 남자화장실
(4, 1, 2, 1, 1, 1, 3, 3, CURRENT_TIMESTAMP); -- SSAFY빌딩 2층 여자화장실
INSERT INTO block VALUES
(1, 1, 1, 1, 1), -- SSAFY빌딩 1층 남자화장실
(2, 1, 1, 2, 1),
(3, 1, 1, 3, 1),
(4, 1, 2, 1, 0),
(5, 1, 2, 2, 0),
(6, 1, 2, 3, 0),
(7, 1, 3, 1, 0),
(8, 1, 3, 2, 0),
(9, 1, 3, 3, 2),
(10, 2, 1, 1, 1), -- SSAFY빌딩 1층 여자화장실
(11, 2, 1, 2, 1),
(12, 2, 1, 3, 1),
(13, 2, 2, 1, 0),
(14, 2, 2, 2, 0),
(15, 2, 2, 3, 0),
(16, 2, 3, 1, 0),
(17, 2, 3, 2, 0),
(18, 2, 3, 3, 2),
(19, 3, 1, 1, 1), -- SSAFY빌딩 2층 남자화장실
(20, 3, 1, 2, 1),
(21, 3, 1, 3, 1),
(22, 3, 2, 1, 0),
(23, 3, 2, 2, 0),
(24, 3, 2, 3, 0),
(25, 3, 3, 1, 0),
(26, 3, 3, 2, 0),
(27, 3, 3, 3, 2),
(28, 4, 1, 1, 1), -- SSAFY빌딩 2층 여자화장실
(29, 4, 1, 2, 1),
(30, 4, 1, 3, 1),
(31, 4, 2, 1, 0),
(32, 4, 2, 2, 0),
(33, 4, 2, 3, 0),
(34, 4, 3, 1, 0),
(35, 4, 3, 2, 0),
(36, 4, 3, 3, 2);
INSERT INTO stall VALUES
(1, 1, 1, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 1), -- 1층남자화장실칸
(2, 1, 2, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 2),
(3, 1, 3, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 3),
(4, 2, 10, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 1), -- 1층여자화장실칸
(5, 2, 11, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 2),
(6, 2, 12, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 3),
(7, 3, 19, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 1), -- 2층남자화장실칸
(8, 3, 20, 1, CURRENT_TIMESTAMP, 0, 1, 3, 5, 1, 0, 2), -- 고장
(9, 3, 21, 0, CURRENT_TIMESTAMP, 1, 1, 0, 2, 0, 0, 3), -- 잠겨있고 사용중
(10, 4, 28, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 1), -- 2층여자화장실칸
(11, 4, 29, 2, CURRENT_TIMESTAMP, 0, 1, 0, 10, 3, 0, 2), -- 점검
(12, 4, 30, 0, CURRENT_TIMESTAMP, 0, 0, 0, 0, 0, 0, 3);
INSERT INTO toilet VALUES
(1, 1, 0),
(2, 2, 0),
(3, 3, 0),
(4, 4, 0),
(5, 5, 0),
(6, 6, 0),
(7, 7, 0),
(8, 8, 1),
(9, 9, 0),
(10, 10, 0),
(11, 11, 0),
(12, 12, 0);
INSERT INTO item VALUES
(1, 1, 100, 0),
(2, 2, 3, 1), -- 휴지 부족
(3, 3, 95, 4),
(4, 4, 76, 0),
(5, 5, 83, 5),
(6, 6, 4, 0), -- 휴지 부족
(7, 7, 60, 0),
(8, 8, 62, 2),
(9, 9, 2, 0), -- 휴지 부족
(10, 10, 100, 3),
(11, 11, 99, 0),
(12, 12, 71, 0);
INSERT INTO report VALUES
(1, 1, 1, '청소가 안 된 부분이 있는 것 같아요', CURRENT_TIMESTAMP, 0),
(2, 8, 3, '고장이 났어요!!', CURRENT_TIMESTAMP, 1);
INSERT INTO user VALUES
(1, '5678', 'ssafyking@gmail.com', '010-3333-3333',
CURRENT_TIMESTAMP, '최싸피', NULL, '인천광역시 부평구');
INSERT INTO bookmark VALUES
(1, 1, CURRENT_TIMESTAMP, 'SSAFY 서울 캠퍼스'),
(2, 1, CURRENT_TIMESTAMP, '국립중앙박물관');
