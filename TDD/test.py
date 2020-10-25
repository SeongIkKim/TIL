# 2부 - xunit 만들기

class TestCase():

    def __init__(self, name):
        self.name = name

    def setUp(self):
        '''
        하위 클래스(WasRun,TestCaseTest)에서 오버라이드할 추상 메서드
        '''
        pass

    def run(self):
        '''
        메서드 동적 호출
        getattr(object, name, default)는 object 내에서 주어진 string(name)과 동일한 method를 반환해준다.
        따라서 테스트케이스의 이름을 전달했을 때, 해당 테스트케이스가 호출되었는지를 기록할 수 있다.
        '''
        self.setUp()
        method = getattr(self, self.name) # 상수를 변수(method)로 변화시켜 일반화하는 리팩토링의 예
        method()


class WasRun(TestCase):
    '''
    메서드가 실행되었는지를 알려주는 테스트클래스
    '''

    def __init__(self, name):
        self.wasRun = None # 테스트케이스가 호출되었는지를 알려주는 어트리뷰트
        TestCase.__init__(self, name)

    def testMethod(self):
        '''
        메서드 호출여부 기록
        메서드가 호출되었는지를 기억(flag)하는 메서드
        '''
        self.wasRun = 1

    def setUp(self):
        '''
        setUp 여부 기록
        여러 테스트를 실행할 때, 테스트 커플링을 피하기 위해(환경을 독립시키기 위해) 사용하는 일종의 세팅 메서드
        '''
        self.wasRun = None
        self.wasSetUp = 1


class TestCaseTest(TestCase):
    '''
    테스트케이스를 수행하는 메인 클래스
    '''

    def setUp(self):
        '''
        WasRun 인스턴스 생성 파트(각 테스트메서드마다 인스턴스를 분리하기 위하여)
        '''
        self.test = WasRun("testMethod")

    def testRunning(self):
        '''
        test 코드 실행 테스트코드
        '''
        # assert(not self.test.wasRun) # test-setUp이 존재하고 잘 돌아가므로 wasRun을 검사할 필요가 없어졌다(단순화)
        self.test.run()
        assert(self.test.wasRun) # 1

    def testSetUp(self):
        '''
        setUp 메서드 호출여부 테스트코드
        '''
        self.test.run()
        assert(self.test.wasSetUp)

# main

TestCaseTest("testRunning").run()
TestCaseTest("testSetUp").run()
