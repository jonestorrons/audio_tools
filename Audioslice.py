from pydub import AudioSegment

def get_audio(audiopath,variable_delay):
    wav_length=[0,7651,5744,6074,6360,8505,5470,7337,5728,6577,6406,5765,4482,5935,7650,6700,8335]
    wav_path=['f1.wav','f2.wav','f3.wav','f4.wav','f5.wav','f6.wav','f7.wav','f8.wav','m1.wav','m2.wav','m3.wav','m4.wav','m5.wav','m6.wav','m7.wav','m8.wav']
    wav_used=variable_delay+0
    for i in range(0,16):
        start_time=wav_length[i]+wav_used
        end_time=wav_length[i]+wav_length[i+1]+wav_used
        wav_used+=wav_length[i+1]
        sound=AudioSegment.from_wav(audiopath)
        outsound=sound[start_time,end_time]
        outsound.export(wav_path[i],format="wav")

if __name__ == '__main__':
    path='test.wav'
    delay=1000
    get_audio(path,delay)
    