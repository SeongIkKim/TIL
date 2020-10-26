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

    def run(self, result):
        '''
        메서드 동적 호출
        '''
        result.testStarted()
        self.setUp()
        try :
            method = getattr(self, self.name)
            method()
        except Exception as e :
            result.testFailed()
            print(e)
        self.tearDown()
        # return result # result를 명시적으로 반환할 필요가 없다! (가져온 result를 조작한 것이므로)


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
        raise Exception

    def tearDown(self):
        '''
        tearDown 여부 기록
        테스트를 위해 setUp에서 할당받은 외부 자원을, 테스트가 종료되면 반환하는 메서드
        '''
        self.log += " tearDown"

class TestSuite:

    def __init__(self):
        self.tests = []

    def add(self, test):
        self.tests.append(test)

    def run(self, result):
        '''
        :param result: 호출부 TestCaseTest.testSuite()에서 만든 result를 매개변수로 받아 그대로 사용한다.
        '''
        for test in self.tests:
            test.run(result)
        # return result # result를 명시적으로 반환할 필요가 없다! (가져온 result를 조작한 것이므로)


class TestCaseTest(TestCase):
    '''
    테스트케이스를 수행하는 메인 클래스
    '''

    def setUp(self):
        '''
        각 메서드마다 TestResult()를 만들고 넘겨주고 할 것 없이, suite이 공유하는 result를 만든다.
        '''
        self.result = TestResult()

    def testTemplateMethod(self):
        '''
        setUp과 tearDown의 호출 순서 체크 테스트코드
        '''
        test = WasRun("testMethod")
        test.run(self.result)
        assert ("setUp testMethod tearDown" == test.log)

    def testResult(self):
        '''
        실행결과가 제대로 나오는지 체크하는 테스트코드
        '''
        test = WasRun("testMethod")
        test.run(self.result)
        assert ("1 run, 0 failed" == self.result.summary())

    def testFailedResult(self):
        '''
        실패하는 테스트 수가 제대로 나오는지 체크하는 테스트코드
        '''
        test = WasRun("testBrokenMethod")
        test.run(self.result)
        assert ("1 run, 1 failed" == self.result.summary())

    def testFailedResultFormatting(self):
        '''
        테스트 시작/실패 메시지 체크 테스트코드
        '''
        self.result.testStarted() # 테스트 시작시 보내는 메시지
        self.result.testFailed() # 테스트 실패시 보내는 메시지
        assert ("1 run, 1 failed" == self.result.summary())

    def testSuite(self):
        suite = TestSuite() # 테스트 스위트 - Composite
        suite.add(WasRun("testMethod")) # 1번 테스트 - 테스트스위트의 Component
        suite.add(WasRun("testBrokenMethod")) # 2번 테스트 - 테스트스위트의 Component
        suite.run(self.result) # 컬렉션을 Component처럼 이용한다. Composite 패턴의 예
        assert ("2 run, 1 failed" == self.result.summary()) # 2개의 테스트를 테스트 스위트로 묶어 수행하고, 1개가 실패했음

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

# 이전까지 하나씩 실행시켰던 것들을 suite로 한번에 묶어 처리한다.
suite = TestSuite()
suite.add(TestCaseTest("testTemplateMethod"))
suite.add(TestCaseTest("testResult"))
suite.add(TestCaseTest("testFailedResultFormatting"))
suite.add(TestCaseTest("testFailedResult"))
suite.add(TestCaseTest("testSuite"))
result = TestResult()
suite.run(result)
print(result.summary())
