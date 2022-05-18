%% ģ���˻���ʾ����
clear;clc;close all;
% �������
minx = -4;maxx = 2; 
% Ŀ�꺯��
fun = @(x) 3*exp(sin(x.^3))-9*cos(x.^2)-5.6*sin(x); 
% ��ʼ������
num = 12;
% ��ʼλ��
loc = minx + (maxx-minx)*rand(1,num);
% ������������ģ���¶�
T = maxx-minx; 
% ��������
Iter = 200;
% �¶�λ��ϵ��
kd = 0.5;
% �¶ȸ���ϵ��,�൱�ڲ�����������
k = 0.01; 
% �¶Ƚ�������
vt = 0.97;
% ��ǰ��
vP = fun(loc);
x = minx:0.01:maxx;
y = fun(x);
% �洢ÿ�������������Ž�
Re = zeros(1,Iter);
% ���ѭ�������¶ȵ������ڲ�ѭ�����ڶ��ʼֵ���
for t = 1:Iter
    % ��ǰ�¶��µ�ƽ���ƶ�����
    dx_av = kd*T; 
    % ���º���¶�
    T = T*vt;
for p = 1:num
        % ��ƽ���ƶ�����Ϊ������̬�ֲ�
        dx = dx_av*normrnd(0,1) + dx_av;
if rand <= 0.5 % �������Ƹ�ռ50%
            dx = - dx;
        end
        locV = loc(p) + dx;
if (locV<maxx) && (locV>minx) %�ж��Ƿ�Խ��
            local_value = fun(locV);
if local_value > vP(p)
                loc(p) = locV;
                vP(p)=local_value;
else
                dltE = local_value-vP(p);
                P = exp(dltE/(k*T));
if rand < P
                    loc(p) = locV;
                    vP(p) = local_value;
                end
            end
        end
    end
    Re(t) = max(vP);
if mod(t,5) == 0
        subplot(2,1,1);
        plot(x,y);
        ylim([min(y)-1 max(y)+1]);
        hold on;
        plot(loc, vP,'r.','MarkerSize',10);
        title('��Ѱ���̶�̬��ʾ');
        ylabel('����ֵ Y');
        xlabel('�Ա��� X');
        hold off;
        subplot(2,1,2);
        plot(1:t,Re(1:t));
        hold on;
        plot(1:t,ones(1,t)*Re(t),'r--');
        ylim([min(Re(1:t))-1 max(Re(1:t))+1]);
        [v,c] = max(vP);
        title(['��ǰ���Ž�: ',num2str([loc(c) v])]);
        ylabel('��ǰ���Ž�');
        xlabel('��������');
        hold off;
        pause(0.05);
    end
end