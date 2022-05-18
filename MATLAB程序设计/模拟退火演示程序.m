%% 模拟退火演示程序
clear;clc;close all;
% 求解区间
minx = -4;maxx = 2; 
% 目标函数
fun = @(x) 3*exp(sin(x.^3))-9*cos(x.^2)-5.6*sin(x); 
% 初始解数量
num = 12;
% 初始位置
loc = minx + (maxx-minx)*rand(1,num);
% 根据区间生成模拟温度
T = maxx-minx; 
% 迭代次数
Iter = 200;
% 温度位移系数
kd = 0.5;
% 温度概率系数,相当于波尔兹曼常数
k = 0.01; 
% 温度降低速率
vt = 0.97;
% 当前解
vP = fun(loc);
x = minx:0.01:maxx;
y = fun(x);
% 存储每个迭代步的最优解
Re = zeros(1,Iter);
% 外层循环用于温度迭代，内层循环用于多初始值求解
for t = 1:Iter
    % 当前温度下的平均移动距离
    dx_av = kd*T; 
    % 更新后的温度
    T = T*vt;
for p = 1:num
        % 以平均移动距离为中心正态分布
        dx = dx_av*normrnd(0,1) + dx_av;
if rand <= 0.5 % 左移右移各占50%
            dx = - dx;
        end
        locV = loc(p) + dx;
if (locV<maxx) && (locV>minx) %判断是否越界
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
        title('搜寻过程动态演示');
        ylabel('函数值 Y');
        xlabel('自变量 X');
        hold off;
        subplot(2,1,2);
        plot(1:t,Re(1:t));
        hold on;
        plot(1:t,ones(1,t)*Re(t),'r--');
        ylim([min(Re(1:t))-1 max(Re(1:t))+1]);
        [v,c] = max(vP);
        title(['当前最优解: ',num2str([loc(c) v])]);
        ylabel('当前最优解');
        xlabel('迭代步数');
        hold off;
        pause(0.05);
    end
end