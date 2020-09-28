from airco import Airco, Cooler, Controller


if __name__ == '__main__':
    print("Testing airco")
    a = Airco()

    print("Adding controller")
    a.controller = Controller()
    print("Adding cooler")
    a.cooler = Cooler()
    print("Adding callback functions")
    cb = lambda running: print(f"[Callback] cooler is{'' if running else ' not'} running")
    a.add_callback(cb)

    print("Starting airco")
    a.start()
    a.temperature(20.5)
    a.temperature(21.2)
    a.temperature(20.6)
    a.temperature(19.9)
    a.temperature(20.4)

    print("Stopping airco")
    a.stop()

    print("Testing inheritance")

    class PyController(Controller):
        def HandleStateChange(self):
            print("PyController handling state change")
            Controller.HandleStateChange(self)

    ctrl = PyController()
    a.controller = ctrl
    a.start()
    print("Setting temperature")
    print("Should show: PyController handling state change:")
    a.temperature(20.5)
    a.temperature(21.3)
    a.temperature(20.6)
    a.temperature(19.5)
    a.stop()


