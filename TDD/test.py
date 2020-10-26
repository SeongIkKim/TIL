# 2부 - xunit 만들기

class TestCase():

    def __init__(self, name):
        self.name = name

    def setUp(self):
        '''
        하위 클래스 WasRun에서 오버라이드할 추상 메서드
        '''
        pass

    def tearDown(self):
        '''
        하위 클래스 WasRun에서 오버라이드할 추상 메서드
        '''
        pass

    def run(self):
        '''
        메서드 동적 호출
        '''
        result = TestResult() # 실행결과 객체 할당
        result.testStarted() # 실행 카운트 기록
        self.setUp() # 이 코드에서 setUp에 문제가 발생했을 경우에는 예외를 잡을 수 없다.
        try :
            method = getattr(self, self.name)
            method()
        except :
            result.testFailed() # 예외 발생시 Failed 카운트 올리기
        self.tearDown()
        return result


class WasRun(TestCase):
    '''
    메서드가 실행되었는지를 알려주는 테스트클래스
    '''

    def __init__(self, name):
        TestCase.__init__(self, name)

    def setUp(self):
        '''
        setUp 여부 기록
        여러 테스트를 실행할 때, 테스트 커플링을 피하기 위해(환경을 독립시키기 위해) 사용하는 일종의 세팅 메서드
        '''
        self.log = "setUp"

    def testMethod(self):
        '''
        테스트메서드 호출여부 기록
        메서드가 호출되었는지를 기억(flag)하는 메서드
        '''
        self.log += " testMethod"

    def testBrokenMethod(self):
        '''
        실패하는 테스트의 stub
        '''
        raise Exception # 이번 장에서는 아직 예외 핸들링을 하지 않았다!

    def tearDown(self):
        '''
        tearDown 여부 기록
        테스트를 위해 setUp에서 할당받은 외부 자원을, 테스트가 종료되면 반환하는 메드서
        '''
        self.log += " tearDown"



class TestCaseTest(TestCase):
    '''
    테스트케이스를 수행하는 메인 클래스
    '''

    def testTemplateMethod(self):
        '''
        setUp과 tearDown의 호출 순서 체크 테스트코드
        '''
        test = WasRun("testMethod")
        test.run()
        assert("setUp testMethod tearDown" == test.log)

    def testFailedResult(self):
        '''
        실패하는 테스트 수가 제대로 나오는지 체크하는 테스트코드
        '''
        test = WasRun("testBrokenMethod")
        result = test.run()
        assert("1 run, 1 failed" == result.summary())

    def testFaieldResultFormatting(self):
        '''
        테스트 시작/실패 메시지 체크 테스트코드
        '''
        result = TestResult()
        result.testStarted() # 테스트 시작시 보내는 메시지
        result.testFailed() # 테스트 실패시 보내는 메시지
        assert("1 run, 1 failed" == result.summary())

    def testResult(self):
        '''
        실행결과가 제대로 나오는지 체크하는 테스트코드
        '''
        test = WasRun("testMethod")
        result = test.run()
        assert("1 run, 0 failed" == result.summary())

class TestResult:
    '''
    테스트메서드(들)의 실행결과를 기록하는 객체
    '''

    def __init__(self):
        self.runCount = 0 # 실행된 테스트의 수 0으로 초기화
        self.failureCount = 0

    def testStarted(self):
        self.runCount = self.runCount + 1

    def testFailed(self):
        self.failureCount += 1

    def summary(self):
        '''
        실행결과 반환 메서드
        '''
        return f"{self.runCount} run, {self.failureCount} failed"

# main

TestCaseTest("testTemplateMethod").run()
