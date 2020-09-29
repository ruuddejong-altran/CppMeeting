from airco import Airco, Temperature, Thermostat, Controller


if __name__ == '__main__':
    print("Testing airco")

    print("Creating thermostat")
    thermostat = Thermostat()

    print("Creating controller")
    controller = Controller()

    print("Creating airco")
    airco = Airco(controller, thermostat)

    print("Adding callback functions")
    cb = lambda running: print(f"[Callback] airco is{'' if running else ' not'} cooling")
    airco.add_callback(cb)

    print("Starting airco")
    airco.start()
    airco.temperature(20.5)
    airco.temperature(21.2)
    airco.temperature(20.6)
    airco.temperature(19.9)
    airco.temperature(20.4)

    print("Stopping airco")
    airco.stop()

    del airco

    print("Testing inheritance")

    class PyController(Controller):
        def signal(self, event):
            print("PyController received event:", event)
            Controller.signal(self, event)


    py_controller = PyController()

    print("Creating airco with inherited controller")
    airco2 = Airco(py_controller, thermostat)
    airco2.add_callback(cb)
    airco2.start()
    print("Setting temperature")
    print("Expected: PyController received event: (but does not happen)")
    airco2.temperature(20.5)
    airco2.stop()


