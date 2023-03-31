
close all
clc
clear
clear('cam')

% find webcam 
cam_list = webcamlist;

cam_name = cam_list{2};

cam = webcam(cam_name);

%%
preview(cam);


%% take picture of image before shapes
closePreview(cam);
data.orig = snapshot(cam);

%% read in image before shapes
%data.orig = imread("Images/NoShapes.jpg");
figure();
imshow(data.orig)
[height,width,depth] = size(data.orig);

%% take picture of camera after shapes are included
data.cur = snapshot(cam);
%data.cur = imread("Images/Basic Shapes.jpg");
figure();
imshow(data.cur)

%% compute difference of two pictures
data.diff = data.orig - data.cur;
figure();
imshow(data.diff)

%% fix image and compute binary
backgroundSub = data.diff;
for i=1:height
    for j=1:width
        if (data.diff(i,j,1) > 20) || ...
           (data.diff(i,j,2) > 20) || ...
           (data.diff(i,j,3) > 20)
            
            %Will Show in Green
            backgroundSub(i,j,:) = [175,200,175];
        end
    end
end

figure();
imshow(backgroundSub);

%%
data.binary = im2bw(backgroundSub);
figure();
imshow(data.binary);

%% Erode Image

SE = strel('disk',6);

data.noise_remove = imerode(data.binary, SE);

figure();
imshow(data.noise_remove);

%%

STATS = regionprops(data.noise_remove, 'all');

figure();
imshow(data.cur);
hold on;

%Ideal Color Combinations
colorsNum = {[255,0,0], [0,255,0], [0,0,255], [255,255,0], [255,0,255], [0,255,255]};
colorsName = ["Red", "Green", "Blue", "Yellow", "Magenta", "Cyan"];

items = size(STATS);
for i = 1:items
    ratio = STATS(i).Perimeter / STATS(i).Area;
    if ratio >= 0.5 && ratio < 1.1
        STATS(i).Shape = "Triangle";
    elseif ratio < 0.5 && ratio >= 0.19
        STATS(i).Shape = "Square";
    elseif ratio < 0.19
        STATS(i).Shape = "Circle";
    else
        STATS(i).Shape = "Invalid";
        continue;
    end
   
    %Find RGB Values at each Centroid
    STATS(i).Red = data.cur(round(STATS(i).Centroid(2)), round(STATS(i).Centroid(1)),1);
    STATS(i).Green = data.cur(round(STATS(i).Centroid(2)), round(STATS(i).Centroid(1)),2);
    STATS(i).Blue = data.cur(round(STATS(i).Centroid(2)), round(STATS(i).Centroid(1)),3);
    
    STATS(i).lowestEuclideanDistance = 1000000;
    for j = 1:size(colorsName,2)
        currDistance = round(sqrt((colorsNum{j}(1) - double(STATS(i).Red))^2 + (colorsNum{j}(2) - double(STATS(i).Green))^2 + (colorsNum{j}(3) - double(STATS(i).Blue))^2));
        if currDistance < STATS(i).lowestEuclideanDistance
            STATS(i).colorIndex = j;
            STATS(i).lowestEuclideanDistance = currDistance;
        end
        STATS(i).Color = colorsName{STATS(i).colorIndex};
    end
    
    %Plot Centroid and Shape Label
    plot(STATS(i).Centroid(1),STATS(i).Centroid(2),'kO','MarkerFaceColor', 'k', 'MarkerSize', 3);
    text(STATS(i).Centroid(1) - 10,STATS(i).Centroid(2) + 25, STATS(i).Shape, 'Color', STATS(i).Color);

end
hold off;


%% GUI
clc;
close all;

figure();
imshow(data.cur);
hold on;
    
for i = 1:items
    plot(STATS(i).Centroid(1),STATS(i).Centroid(2),'kO','MarkerFaceColor', 'k', 'MarkerSize', 3);
    text(STATS(i).Centroid(1) - 10,STATS(i).Centroid(2) + 25, STATS(i).Shape, 'Color', STATS(i).Color);
end

%Offset from top left corner of the figure to the top left corner of the
%image
imageSize = [640, 480];
offsetToImage = [182, 54];

% Varialbe Motor Location
% Calls the funciton to prompt the user to choose a shape
fprintf("Motor Location\n");
shapeChoice1 = chooseShapes(STATS, items);
clc;

cont = 1;
while (cont == 1)
    fprintf("Desired Variable Location\n");
    shapeChoice2 = chooseShapes(STATS, items);
    clc;
    
    % A set of points for the motor (first selection), reference (directly
    % above the motor point, and the variable angle (second selection);
    variableArrowPoint1 = [STATS(shapeChoice1).Centroid(1), STATS(shapeChoice1).Centroid(2)];
    variableArrowPoint2 = [STATS(shapeChoice2).Centroid(1), STATS(shapeChoice2).Centroid(2)];
    relativePoint1 = [0, (STATS(shapeChoice1).Centroid(2) - offsetToImage(2))];
    relativePoint2 = [-(variableArrowPoint1(1) - variableArrowPoint2(1)), (variableArrowPoint1(2) - variableArrowPoint2(2))];
    
    % Motor being at position 1
    quiver(variableArrowPoint1(1), variableArrowPoint1(2), relativePoint1(1), -relativePoint1(2), 0, "LineWidth", 2, "Color", STATS(shapeChoice1).Color);
    text((variableArrowPoint1(1) + 10), offsetToImage(2) + 10, "Reference", 'Color', STATS(shapeChoice1).Color, 'FontSize', 20);
    quiver(variableArrowPoint1(1), variableArrowPoint1(2), relativePoint2(1), -(relativePoint2(2)), 0, "LineWidth", 2, "Color", STATS(shapeChoice1).Color);
    
    % Calculate the angle between the reference and the variable arrows
    angle = acos(((relativePoint1(1) * relativePoint2(1)) + (relativePoint2(2) * relativePoint1(2))) / ...
        ((((relativePoint1(1))^2 + (relativePoint1(2))^2)^0.5) * (((relativePoint2(1))^2 + (relativePoint2(2))^2)^0.5)));
    angle = round((angle * 180 / pi), 2);
    
    dot = relativePoint1(1)*relativePoint2(1) + relativePoint1(2)*relativePoint2(2);
    det = relativePoint1(1)*relativePoint2(2) - relativePoint1(2)*relativePoint2(1);
    motorAngle = atan2(det, dot);
    motorAngle = round((motorAngle * 180 / pi), 2);
    
    str_angle = num2str(mod(motorAngle, 360));
    set_param('MotorModel_Sp23_V21b/desiredPosition', 'Value', str_angle);
    
    % Display an arc between reference and varaible arrows as well as the angle
    % Define parameters of the arc.
    %Change OriginImagePoints 1 an 2 to change origin of the arc
    radius = 50;
    % Define the angle theta as going from 90 degrees to the angle in degrees in 100 steps.
    if (relativePoint2(1) >= 0)
        % Define x and y using "Degrees" version of sin and cos.
        theta = linspace(angle-90, -90, 100);
        x = radius * cosd(theta) + variableArrowPoint1(1); 
        y = radius * sind(theta) + variableArrowPoint1(2);
    else
        theta = linspace(-90, angle-90, 100);
        % Define x and y using "Degrees" version of sin and cos.
        x = radius * -cosd(theta) + variableArrowPoint1(1); 
        y = radius * sind(theta) + variableArrowPoint1(2);
    end
    
    % Now plot the points.
    plot(x, y, "Color", STATS(shapeChoice1).Color, 'LineWidth', 2); 
    %text(variableArrowPoint1(1) + 5, (variableArrowPoint1(2) - 100), "\theta = " + angle, 'Color', STATS(shapeChoice1).Color, 'FontSize', 12);
    text(variableArrowPoint1(1) + 5, (variableArrowPoint1(2) - 100), "\theta = " + angle, 'Color', 'k', 'FontSize', 12);
    
    cont = 2;
    while (cont ~= 1 && cont ~= 0)
        cont = input("Continue? (1/0):");
        if (cont ~= 1 && cont ~= 0)
            fprintf("Error incorrect input\n");
            fprintf("%d", cont);
        end
    end
end

set_param('MotorModel_Sp23_V21b/desiredPosition', 'Value', '0');

%desiredPosition = angle;

% Motor being at the origin
% % Plot the reference arrow and text as well as the variable arrow
% quiver(originImagePoint(1), originImagePoint(2), refernceArrowPoint(1), refernceArrowPoint(2), 0, "LineWidth", 2, "Color", STATS(shapeChoice1).Color);
% text(offsetToImage(1) + 20, offsetToImage(2) + 10, "Reference", 'Color', STATS(shapeChoice1).Color, 'FontSize', 20);
% quiver(offsetToImage(1), (offsetToImage(2) + imageSize(2)), variableArrowPoint1(1), variableArrowPoint1(2), 0, "LineWidth", 2, "Color", STATS(shapeChoice1).Color);
% 
% % Calculate the angle between the reference and the variable arrows
% angle = acos(((refernceArrowPoint(1) * variableArrowPoint1(1)) + (variableArrowPoint1(2) * refernceArrowPoint(2))) / ...
%     ((((refernceArrowPoint(1))^2 + (refernceArrowPoint(2))^2)^0.5) * (((variableArrowPoint1(1))^2 + (variableArrowPoint1(2))^2)^0.5)));
% angle = round((angle * 180 / pi), 2);
% 
% % Display an arc between reference and varaible arrows as well as the angle
% % Define parameters of the arc.
% %Change OriginImagePoints 1 an 2 to change origin of the arc
% radius = 50;
% % Define the angle theta as going from 30 to 150 degrees in 100 steps.
% theta = linspace(angle-90, -90, 100);
% % Define x and y using "Degrees" version of sin and cos.
% x = radius * cosd(theta) + originImagePoint(1); 
% y = radius * sind(theta) + originImagePoint(2); 
% % Now plot the points.
% plot(x, y, "Color", STATS(shapeChoice1).Color, 'LineWidth', 2); 
% text(offsetToImage(1) + 5, (originImagePoint(2) - 100), "\theta = " + angle, 'Color', STATS(shapeChoice1).Color, 'FontSize', 12);
% 
% desiredPosition = angle;


% Function that prompts the user for shape selection
function shapeChoice = chooseShapes(STATS, items)
    % Displays the list of shapes for the user to choose from
    fprintf("Select a shape from the list below: \n");
    for i = 1:items
        fprintf("%d. %s\n", i, strcat(STATS(i).Color, " ", STATS(i).Shape));
    end
    shapeChoice = input("Enter the Number for the chosen Shape: ");
    
    % Make sure the user imput is valid
    while or((shapeChoice < 1), (shapeChoice > items))
        fprintf("\n\nPlease Try Again, %d is not a vaild choice\n", shapeChoice);
        fprintf("Enter and Number between 1 and %d\n", items(1));
        
        % If the input is invalid, prompt them again
        fprintf("Select a shape from the list below: \n");
        for i = 1:items
            fprintf("%d. %s\n", i, strcat(STATS(i).Color, " ", STATS(i).Shape));
        end
        shapeChoice = input("Enter the Number for the chosen Shape: ");
    end
    
    % Plot a green dot at the centroid of the selected shape
    plot(STATS(shapeChoice).Centroid(1),STATS(shapeChoice).Centroid(2),'kO','MarkerFaceColor', [0, 0.9, 0.2], 'MarkerEdgeColor', [1, 1, 0.2], 'MarkerSize', 10);

% Uncommet to prompt the user to confirm their shape selection
%     checkChoseShapeVal = checkChosenShape();
%     if (checkChoseShapeVal == 0)
%         chooseShapes(data, STATS, items);
%     else 
%        fprintf("Shape Choice is %d. %s\n", shapeChoice, strcat(STATS(shapeChoice).Color, " ", STATS(shapeChoice).Shape))
%     end
    
end

% Function to prompt the user to ensure they chose the correct shape
function shapeCheck = checkChosenShape()
    shapeCheck = input("Is the highlighted shape correct? (1/0): ");
    
    % Make sure they input a 1 or 0
    while ((shapeCheck ~= 1) && (shapeCheck ~= 0))
        fprintf("Invalid Entry\n");
        shapeCheck = input("Is the highlighted shape correct? (1/0): ");
    end

end