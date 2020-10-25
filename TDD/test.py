# 2부 - xunit 만들기

class TestCase:
    def __init__(self, name):
        self.name = name

    def run(self):
        '''
        메서드 동적 호출
        getattr(object, name, default)는 object 내에서 주어진 string(name)과 동일한 method를 반환해준다.
        따라서 테스트케이스의 이름을 전달했을 때, 해당 테스트케이스가 호출되었는지를 기록할 수 있다.
        '''
        method = getattr(self, self.name) # 상수를 변수(method)로 변화시켜 일반화하는 리팩토링의 예
        method()


class WasRun(TestCase):
    def __init__(self, name):
        self.wasRun = None # 테스트케이스가 호출되었는지를 알려주는 어트리뷰트
        TestCase.__init__(self, name)

    def testMethod(self):
        '''
        메서드 호출여부 기록
        메서드가 호출되었는지를 기억(flag)하는 메서드
        '''
        self.wasRun = 1


class TestCaseTest(TestCase):
    def testRunning(self):
        '''
        test 코드 실행 메서드
        실행 과정을 print문이 아니라 assertion 형태로 구현
        '''
        test = WasRun("testMethod")
        assert(not test.wasRun) # not None이므로, True 반환
        test.run() # testMethod()를 직접 호출하지 않고, run()이라는 함수를 두어 두 부분을 분리함
        assert(test.wasRun) # 1

# main

TestCaseTest("testRunning").run() # 성공!

