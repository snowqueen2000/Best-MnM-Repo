function varargout = Lab3_GUI(varargin)
% LAB3_GUI MATLAB code for Lab3_GUI.fig
%      LAB3_GUI, by itself, creates a new LAB3_GUI or raises the existing
%      singleton*.
%
%      H = LAB3_GUI returns the handle to a new LAB3_GUI or the handle to
%      the existing singleton*.
%
%      LAB3_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in LAB3_GUI.M with the given input arguments.
%
%      LAB3_GUI('Property','Value',...) creates a new LAB3_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Lab3_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Lab3_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Lab3_GUI

% Last Modified by GUIDE v2.5 10-Jan-2018 17:06:00

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Lab3_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Lab3_GUI_OutputFcn, ...
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


% --- Executes just before Lab3_GUI is made visible.
function Lab3_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Lab3_GUI (see VARARGIN)

% Choose default command line output for Lab3_GUI
handles.output = hObject;

%create DAQ sessions
handles.Ain= daq.createSession('ni');

%define session settings for s (scope, Analog input)
%addAnalogInputChannel(session, DAQ device, channel, Voltage/Current)
CH0 = addAnalogInputChannel(handles.Ain,'Dev1',0,'Voltage');
CH1 = addAnalogInputChannel(handles.Ain,'Dev1',1,'Voltage');
CH0.TerminalConfig = 'SingleEnded';     
CH1.TerminalConfig = 'SingleEnded';

%create D output channel
handles.Dout = daq.createSession('ni');

%define session settings for Digital output
%addDigitalChannel(session, DAQ device, channel, output/input)
addDigitalChannel(handles.Dout,'Dev1','port0/line0','OutputOnly');

%create A output channel
handles.Aout = daq.createSession('ni');

%define session settings for Analog output
%addAnalogOutputChannel(session, DAQ device, channel,Voltage/current)
addAnalogOutputChannel(handles.Aout,'Dev1','ao0','Voltage');
outputSingleScan(handles.Aout,[2.5]);

%Format plot 1
axes(handles.Oscope_axes);
title('Oscilloscope')
xlabel('Time (sec)')
ylabel('Voltage (V)')

%format plot 2
axes(handles.FFT_axes);
title('Spectral Analysis')
xlabel('Frequency (Hz)')
ylabel('Magnitude')

        
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Lab3_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Lab3_GUI_OutputFcn(hObject, eventdata, handles) 
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

% Hint: get(hObject,'Value') returns toggle state of Run_button

    while hObject.Value  %while toggle button pressed
        
        %sets up data acquisitoin rate and sample time
        handles.Ain.Rate = str2double(handles.rate_box.String);
        rate = handles.Ain.Rate;
        numSamples = str2double(handles.samples_box.String);
        handles.Ain.DurationInSeconds = numSamples/rate;
        
        %Gather data based on rate and number of samples    
        [handles.Data,handles.Time] = handles.Ain.startForeground;
        data = handles.Data;
        time = handles.Time;
        
        
        %Plot Raw data
        axes(handles.Oscope_axes);
        plot(time,data)
        
        title('Oscilloscope')
        xlabel('Time (sec)')
        ylabel('Voltage (V)')
        legend('CH0','CH1')

        %Signal amplitudes
        min1 = min(data(:,1));
        max1 = max(data(:,1));
        handles.amp0.String = num2str(max1-min1);
        
        min2 = min(data(:,2));
        max2 = max(data(:,2));
        handles.amp1.String = num2str(max2-min2);
        
        
        %scale axis of Oscope_axes
        amp1 = max1-min1;
        amp2 = max2-min2;
        Min_ax = min([min1 min2])-0.1*max([amp1 amp2]);
        Max_ax = max([max1 max2])+0.1*max([amp1 amp2]);
        axis([0 str2double(handles.Oscope_scale.String) Min_ax Max_ax]);
              
        
        %FFT Calculation and Plotting               
                
        % Students should calculate Mag0, Mag1, phase1, phase2, and freq 
        % in this section.
        %------------------------------------------------------------
        % 
         [Mag1,phase1,freq]=fft_sample(data(:,1)-mean(data(:,1)),rate);
         [Mag2,phase2,freq]=fft_sample(data(:,2)-mean(data(:,2)),rate);
        %
        %------------------------------------------------------------
                
        handles.specAnalysis = [freq' Mag1 Mag2]; %make data a handle
        
        axes(handles.FFT_axes);             %switch to FFT_axes
        plot(freq,Mag1)                     %plot CH0
        hold on
        plot(freq,Mag2)                     %plot CH1
        hold off
        title('Spectral Analysis')
        xlabel('Frequency (Hz)')
        ylabel('Magnitude')
        drawnow;                            %force all plot to happen now
               
        %find the average voltage of each channel and send to GUI boxes
        handles.avgV0.String = num2str(mean(data(:,1)));
        handles.avgV1.String = num2str(mean(data(:,2)));
        
        %Find maximum amplitude 
        [~,max_ind1] = max(Mag1); 
        [~,max_ind2] = max(Mag2);
                          
        %phase shift
        phase_shift = phase2(max_ind2)-phase1(max_ind1);                    
        % phase_shift = phase2 - phase1;                    

        %Constrain phase shift from -180 to 180 deg range
        if (phase_shift>180)
            phase_shift=phase_shift-360;
        end
        if(phase_shift<-180)
            phase_shift=phase_shift+360;
        end

        %----------------------------
        % Insert code to calculate the phase difference and find the index 
        % of the primary frequency
        %----------------------------
        
        % set phase_shift box values
        handles.phase_shift.String = num2str(phase_shift);
        
        % find the primary frequencies and assign them to the edit boxes
        handles.freq0.String = num2str(freq(max_ind1));
        handles.freq1.String = num2str(freq(max_ind2));   
        
        %Update handles for the rest of GUI
        guidata(hObject, handles); 
    end
    %while not pressed set value to 0
    



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


% --- Executes on button press in Save_button.
function Save_button_Callback(hObject, eventdata, handles)
% hObject    handle to Save_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

filename = handles.savefile_box.String;
rawdata = [handles.Time handles.Data];

save(filename,'rawdata');



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

% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    handles.Run_button.Value = 0;
    pause(3);

    handles.Ain.release;

    outputSingleScan(handles.Dout,[0]);
    handles.Dout.release;

    outputSingleScan(handles.Aout,[0]);
    handles.Aout.release;

% Hint: delete(hObject) closes the figure
delete(hObject);


% --- Executes on button press in LEDbutton.
function LEDbutton_Callback(hObject, eventdata, handles)
% hObject    handle to LEDbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

onvalue = get(hObject,'Value');
if onvalue == 0
    hObject.String = 'OFF';                        %change string
    hObject.BackgroundColor = [0.769 0.247 0.247]; %change color

    handles.Analog_slider.Value = 0.5;          %set slider to center
    handles.slider_display.String = '0.0 V'; %set slider voltage to 0
    outputSingleScan(handles.Aout,[2.5]);             %Start analog output

else
    hObject.String = 'ON';                          %change string
    hObject.BackgroundColor = [0 0.498 0];           %change color

end

outputSingleScan(handles.Dout,[onvalue]);         %start digital output



% --- Executes on slider movement.
function Analog_slider_Callback(hObject, eventdata, handles)
% hObject    handle to Analog_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

    slider_val = get(hObject,'Value');        
    Mval = 5*slider_val;
    show_val = 10*slider_val-5;
    handles.slider_display.String = [num2str(show_val),' V'];  
    outputSingleScan(handles.Aout,[Mval]);
    
            
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



function freq0_Callback(hObject, eventdata, handles)
% hObject    handle to freq0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of freq0 as text
%        str2double(get(hObject,'String')) returns contents of freq0 as a double


% --- Executes during object creation, after setting all properties.
function freq0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to freq0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function freq1_Callback(hObject, eventdata, handles)
% hObject    handle to freq1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of freq1 as text
%        str2double(get(hObject,'String')) returns contents of freq1 as a double


% --- Executes during object creation, after setting all properties.
function freq1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to freq1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function phase_shift_Callback(hObject, eventdata, handles)
% hObject    handle to phase_shift (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of phase_shift as text
%        str2double(get(hObject,'String')) returns contents of phase_shift as a double


% --- Executes during object creation, after setting all properties.
function phase_shift_CreateFcn(hObject, eventdata, handles)
% hObject    handle to phase_shift (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Oscope_scale_Callback(hObject, eventdata, handles)
% hObject    handle to Oscope_scale (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Oscope_scale as text
%        str2double(get(hObject,'String')) returns contents of Oscope_scale as a double


% --- Executes during object creation, after setting all properties.
function Oscope_scale_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Oscope_scale (see GCBO)
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
