class AbstractHandler:
    def open(self, test):
        raise NotImplementedError()

    def save(self, test):
        raise NotImplementedError()

    def create_empty_test(self, test):
        raise NotImplementedError()

    def save_as_new(self, test):
        raise NotImplementedError()
