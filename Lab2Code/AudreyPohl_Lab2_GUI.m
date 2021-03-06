function varargout = AudreyPohl_Lab2_GUI(varargin)
% AUDREYPOHL_LAB2_GUI MATLAB code for AudreyPohl_Lab2_GUI.fig
%      AUDREYPOHL_LAB2_GUI, by itself, creates a new AUDREYPOHL_LAB2_GUI or raises the existing
%      singleton*.
%
%      H = AUDREYPOHL_LAB2_GUI returns the handle to a new AUDREYPOHL_LAB2_GUI or the handle to
%      the existing singleton*.
%
%      AUDREYPOHL_LAB2_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in AUDREYPOHL_LAB2_GUI.M with the given input arguments.
%
%      AUDREYPOHL_LAB2_GUI('Property','Value',...) creates a new AUDREYPOHL_LAB2_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before AudreyPohl_Lab2_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to AudreyPohl_Lab2_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES


% Edit the above text to modify the response to help AudreyPohl_Lab2_GUI

% Last Modified by GUIDE v2.5 25-Jan-2022 19:51:36

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @AudreyPohl_Lab2_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @AudreyPohl_Lab2_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before AudreyPohl_Lab2_GUI is made visible.
function AudreyPohl_Lab2_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to AudreyPohl_Lab2_GUI (see VARARGIN)

% Choose default command line output for AudreyPohl_Lab2_GUI
handles.output = hObject;

%Format plot 1
axes(handles.Oscope_axes);
title('Oscilloscope');
xlabel('Time (sec)');
ylabel('Voltage (V)');

% create DAQ Sessions
handles.Ain = daq.createSession('ni');

% define session settings for s (scope, analog input)
% addAnalogInputChannel(session, DAQ device, channel, Voltage/Current)
CH0 = addAnalogInputChannel(handles.Ain, 'Dev1', 0, 'Voltage');
CH1 = addAnalogInputChannel(handles.Ain, 'Dev1', 1, 'Voltage');
CH0.TerminalConfig = 'SingleEnded';
CH1.TerminalConfig = 'SingleEnded';

%create D output channel
handles.Dout = daq.createSession('ni');

%define session settings for Digital output
%addDigitalChannel(session, DAQ device, channel, output/input);
addDigitalChannel(handles.Dout,'Dev1', 'port0/line0','OutputOnly');

% create A output channel
handles.Aout = daq.createSession('ni');

% define session settings for analog input
%addAnalogOutputChannel(session, DAQ device, channel, Voltage/current);
addAnalogOutputChannel(handles.Aout, 'Dev1', 'ao0', 'Voltage');
outputSingleScan(handles.Aout,[2.5]);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes AudreyPohl_Lab2_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = AudreyPohl_Lab2_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Run_button.
function Run_button_Callback(hObject, eventdata, handles)
% hObject    handle to Run_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
while hObject.Value
       handles.Ain.Rate = str2double(handles.rate_box.String);
       rate = handles.Ain.Rate;
       numSamples = str2double(handles.samples_box.String);
       handles.Ain.DurationInSeconds = numSamples/rate;
       
       % Uncomment these lines once you are in lab. They refer to the daq
       % system and will not run properly until you are in the lab and
       % complete the first step of the lab
          [handles.Data,handles.Time]=handles.Ain.startForeground
          data = handles.Data;
          time = handles.Time;
       
       % Comment out these lines once you in lab. They are added here so
       % your GUI will plot something in the prelab
%        time = 0:1/rate:numSamples/rate;
%        data = sin(10*time);
       
       % Plot raw data
       axes(handles.Oscope_axes);
       plot(time, data);
       title('Oscilloscope');
       ylabel('Voltage (V)');
       xlabel('Time (sec)');
       
       % Update handles in GUI
       guidata(hObject, handles);

       %Signal Amplitudes
       min1 = min(data(:, 1));
       max1 = max(data(:, 1));
       handles.amp0.String = num2str(max1 - min1);
       
       min2 = min(data(:, 2));
       max2 = max(data(:, 2));
       handles.amp1.String = num2str(max2 - min2);
       
       % average voltage
       handles.avgV0.String = num2str(mean(data(:,1)));
       handles.avgV1.String = num2str(mean(data(:,2)));
 
end

% while not pressed set value to 0
hObject.Value = 0;


function rate_box_Callback(hObject, eventdata, handles)
% hObject    handle to rate_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rate_box as text
%        str2double(get(hObject,'String')) returns contents of rate_box as a double


% --- Executes during object creation, after setting all properties.
function rate_box_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rate_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function samples_box_Callback(hObject, eventdata, handles)
% hObject    handle to samples_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of samples_box as text
%        str2double(get(hObject,'String')) returns contents of samples_box as a double


% --- Executes during object creation, after setting all properties.
function samples_box_CreateFcn(hObject, eventdata, handles)
% hObject    handle to samples_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Save_button.
function Save_button_Callback(hObject, eventdata, handles)
% hObject    handle to Save_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)\

filename = handles.savefile_box.String;
rawdata = [handles.Time handles.Data];
save(filename,'rawdata');



function savefile_box_Callback(hObject, eventdata, handles)
% hObject    handle to savefile_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of savefile_box as text
%        str2double(get(hObject,'String')) returns contents of savefile_box as a double


% --- Executes during object creation, after setting all properties.
function savefile_box_CreateFcn(hObject, eventdata, handles)
% hObject    handle to savefile_box (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function amp1_Callback(hObject, eventdata, handles)
% hObject    handle to amp1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of amp1 as text
%        str2double(get(hObject,'String')) returns contents of amp1 as a double


% --- Executes during object creation, after setting all properties.
function amp1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to amp1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function amp0_Callback(hObject, eventdata, handles)
% hObject    handle to amp0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of amp0 as text
%        str2double(get(hObject,'String')) returns contents of amp0 as a double


% --- Executes during object creation, after setting all properties.
function amp0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to amp0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function avgV0_Callback(hObject, eventdata, handles)
% hObject    handle to avgV0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of avgV0 as text
%        str2double(get(hObject,'String')) returns contents of avgV0 as a double


% --- Executes during object creation, after setting all properties.
function avgV0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to avgV0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function avgV1_Callback(hObject, eventdata, handles)
% hObject    handle to avgV1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of avgV1 as text
%        str2double(get(hObject,'String')) returns contents of avgV1 as a double


% --- Executes during object creation, after setting all properties.
function avgV1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to avgV1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.Run_button.Value = 0;
pause(3);

handles.Ain.release;

% Hint: delete(hObject) closes the figure
delete(hObject);

outputSingleScan(handles.Aout,[0]);
handles.Aout.release;

outputSingleScan(handles.Dout,[0]);
handles.Dout.release;

% --- Executes on button press in LEDbutton.
function LEDbutton_Callback(hObject, eventdata, handles)
% hObject    handle to LEDbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of LEDbutton

onvalue = hObject.Value;
if onvalue == 0
    hObject.String = 'OFF';                         %Change string
    hObject.BackgroundColor = [0.769 0.247 0.247]; %change color
    
    handles.Analog_slider.Value = 0.5; % set slider to center 
    handles.slider_display.String = '0.0 V'; % set slider voltage to 0
    outputSingleScan(handles.Aout, [2.5]); % start analog output
    
else
    hObject.String = 'ON';                         %Change string
    hObject.BackgroundColor = [0 0.498 0]; %change color
    
%     handles.Analog_slider.Value = 0.5; % set slider to center 
%     handles.slider_display.String = '0.0 V'; % set slider voltage to 0
%     outputSingleScan(handles.Aout, [2.5]); % start analog output
    
end
    
outputSingleScan(handles.Dout,[onvalue]);


% --- Executes on slider movement.
function Analog_slider_Callback(hObject, eventdata, handles)
% hObject    handle to Analog_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

slider_val = hObject.Value;
Mval = 5*slider_val;
show_val = 10*slider_val-5;
handles.slider_display.String = [num2str(show_val), ' V '];
outputSingleScan(handles.Aout, [Mval]);


% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function Analog_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Analog_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function slider_display_Callback(hObject, eventdata, handles)
% hObject    handle to slider_display (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of slider_display as text
%        str2double(get(hObject,'String')) returns contents of slider_display as a double


% --- Executes during object creation, after setting all properties.
function slider_display_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_display (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
