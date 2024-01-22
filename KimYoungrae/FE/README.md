
## 컴포넌트
컴포넌트는 component라는 폴더 아래에 만드는게 일반적

```
function 함수명() {

    return (태그들);
}

export default 함수명

import 함수명 from '경로';
```

리턴시 괄호로

export defualt 함수명

<br>

## 이벤트

```
function 함수명() {
    function 이벤트함수1() {
	console.log(...);
    }

    function 이벤트함수2() {
	...
	return ...
    }

    

    return (
	<button onClick={이벤트함수1}>sdsf</button> // 함수 자체를 실행
	<button onClick={이벤트함수2()}>sdsf</button> // 함수의 리턴값을 줌
    <button 
        onClick={()=>{
            console.log(30);
        }}
    >
    );
}




export default 함수명

import 함수명 from '경로';
```

이벤트에 함수를 넣을 시 
함수명 과 함수명()은 다른 의미를 가짐


<br>

## CSS 
```
css파일명 : 컴포넌트이름.module.css

import styles from "./css파일명";


<태그 className={styles.box}>ㅁㄴㅇ</태그>
```

컴포넌트 아래에 컴포넌트.js와 컴포넌트.module.css를 같이 둔다.
이떄, 컴포넌트 숫자가 많아지면 component폴더 아래에 전용 폴더를 하나 더 생성한다.

