# add-nbo 과제

-[참고자료](https://gitlab.com/gilgil/sns/-/wikis/byte-order/report-add-nbo)

> 32 bit 숫자가 파일에 4바이트의 크기로 저장되어 있다(network byte order). 2개의 파일로부터 숫자를 읽어 들여 그 합을 출력하는 프로그램을 작성하라.

## 상세
* 4바이트 정수를 처리하기 위해서 uint32_t 형식을 사용한다(stdint.h 파일을 include하면 uint32_t를 사용할 수 있음).
* 파일에서 숫자을 읽기 위해서는 fopen, fread 함수 등을 사용한다. fopen하고 나서 fclose 함수도 호출해 주도록 한다. 관련 함수들의 사용 방법은 검색을 통하여 익힌다.
* 정수 덧셈에서 발생하는 overflow는 무시한다.
* 파일이 제대로 열리지 않는 경우, 파일의 크기가 4바이트보다 작아서 제대로 읽지 못했다고 판단되는 경우 등에 대해서 에러 처리를 할 수 있도록 한다.

## 설명
### main
* `uint32_t`형식의 data배열 선언
* `readFile`을 통하여 파일을 읽고 파일이 정상적으로 읽힌 경우 data 배열에 포인터를 통하여 자료 저장
* `printf`를 통하여 형식에 맞게 데이터 출력

### readFile
> `void readFile(char* path, uint32_t *data)`
* `File` 포인터를 선언 한 후 path로 입력 된 경로의 파일을 읽기
    * 이 떄, 파일이 존재하지 않는 등의 이유로 정상적으로 열리지 않은 경우에는 File 포인터가 NULL이 리턴되는 것을 통하여 에러처리
* `fseek`를 통하여 파일의 끝까지 파일포인터를 미루어 파일의 전체 크기를 확인
    * 파일의 전체 크기가 `uint32_t(8Byte)`와 일치하지 않은 경우 에러처리
* `fread`를 통하여 `*data`위치에 읽은 데이터 저장
* 읽은 데이터를 `ntohl`함수를 통하여 **NBO**->**HBO** 전환
* `fclose`를 통하여 파일 포인터 닫기
* 명시적으로 파일 포인터를 `NULL`로 초기화


### error
> `void error(int n)`
* `n`을 통해 에러 종류를 입력받고 그에 맞는 출력 후 프로그램 종료
    1. `n == 1`인 경우는 파일 read Error
    2. `n == 2`인 경우 파일 크기 Error
    3. 그 외인 경우 Unknown Error