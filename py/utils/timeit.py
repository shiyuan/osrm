import time

def timeit(method):
    def timed(*args, **kw):
        tic = time.time()
        result = method(*args, **kw)
        tac = time.time()
        print('method: {}, args: {}, cost: {:.2f}ms'.format(method, args, (tac - tic) * 1e3))
        return result
    return timed

