from airco import Controller


class PyController(Controller):
    def HandleStateChange(self):
        print("PyController handling state change")
        Controller.HandleStateChange(self)

