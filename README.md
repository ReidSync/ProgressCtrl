# ProgressCtrl

C++ library for calculating the progress of nested or combined functions.

## Usage
### UI Class (App)
```C++
static void ProgressViewCallback(int progress, void* context) {
	UIClass* view = (UIClass*)context;
	view->ProgressView(progress);
}

SomeProcessor->registerCallback(ProgressViewCallback, this);
```

### Some Processor
```C++
ProgressCtrl* _progress_ctrl = new ProgressCtrl()

void registerCallback(ProgressCallbackFunction progress_callback_function, void* context) {
    _progress_ctrl->SetCallbackMethod(progress_callback_function, context);
    _progress_ctrl->SetGlobalMax(100);
}
```

```C++
void main() {
    _progress_ctrl->StartProgress();

    // 50%
    _progress_ctrl->SetLocalProgressPercentage(50)
    _progress_ctrl->SetProgress(0);
    processMain_1()
    _progress_ctrl->SetProgress(100);

    // 50%
    _progress_ctrl->SetLocalProgressPercentage(50)
    _progress_ctrl->SetProgress(0);
    processMain_2()
    _progress_ctrl->SetProgress(100);


    _progress_ctrl->EndProgress();
}

void processMain_1() {
    _progress_ctrl->StartProgress();

    // 40%
    _progress_ctrl->SetLocalProgressPercentage(40)
     for (int i = 0; i < 40; i++) {
        ...
        _progress_ctrl->SetProgress(i*(100/40));
    }
    _progress_ctrl->SetProgress(100);


    // 20%
    _progress_ctrl->SetLocalProgressPercentage(20)
    processA()
    _progress_ctrl->SetProgress(100);

    
    // 30%
    _progress_ctrl->SetLocalProgressPercentage(30)
    processB()
    _progress_ctrl->SetProgress(100);


    // 10%
    _progress_ctrl->SetLocalProgressPercentage(10)
    for (int i = 0; i < 10; i++) {
        ...
        _progress_ctrl->SetProgress(i*(100/10));
    }
    _progress_ctrl->SetProgress(100);

    _progress_ctrl->EndProgress();
}

void processA() {
    _progress_ctrl->StartProgress();

    // 100%
    _progress_ctrl->SetLocalProgressPercentage(100)
    for(int i = 0; i < 20; i++) {
        ...
        _progress_ctrl->SetProgress(i*(100/20));
    }
    _progress_ctrl->SetProgress(100);

    _progress_ctrl->EndProgress();
}

void processB() {
    _progress_ctrl->StartProgress();

    // 100%
    _progress_ctrl->SetLocalProgressPercentage(100)
    for(int i = 0 < i < 30; i++>) {
        ...
        _progress_ctrl->SetProgress(i*(100/30));
    }
    _progress_ctrl->SetProgress(100);

    _progress_ctrl->EndProgress();
}


void processMain_2() {
    _progress_ctrl->StartProgress();

    // 40%
    _progress_ctrl->SetLocalProgressPercentage(40)
     for (int i = 0; i < 40; i++) {
        ...
        _progress_ctrl->SetProgress(i*(100/40));
    }
    _progress_ctrl->SetProgress(100);


    // 20%
    _progress_ctrl->SetLocalProgressPercentage(20)
    processA()
    _progress_ctrl->SetProgress(100);

    
    // 30%
    _progress_ctrl->SetLocalProgressPercentage(30)
    processB()
    _progress_ctrl->SetProgress(100);


    // 10%
    _progress_ctrl->SetLocalProgressPercentage(10)
    for (int i = 0; i < 10; i++) {
        ...
        _progress_ctrl->SetProgress(i*(100/10));
    }
    _progress_ctrl->SetProgress(100);

    _progress_ctrl->EndProgress();
}

```
