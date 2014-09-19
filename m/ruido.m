function [I]=ruido(I,tipo,parametro)
% [I]=ruido(I,tipo,parametro) funcion que devuelve la imagen original
% más ruido. Los ruidos pueden ser del tipo gaussiano o "sal y pimienta".
% El parametro "tipo" toma los valores 'gauss' para el ruido gaussiano y el
% valor 'syp' para el ruido sal y pimienta.
% El parametro "parametro" en el caso del ruido gaussiano es el factor
% multiplicativo del ruido normalizado, y para el caso del ruido sal y pi-
% mienta es el valor del delta.
%
% Ejemplo      
% ----------
% I=imread('lena.bmp');
% figure,imshow(I)
% [I]=ruido(I,'syp',0.01);
% figure,imshow(I)
%
switch tipo
    case 'gauss'
        
        %Genero ruido gaussiano
        ruido_gauss=randn(size(I))*(parametro/255);
        I=im2double(I)+double(ruido_gauss);

    case 'syp'
        
        %Genero ruido sal y pimienta
        ruido_syp=rand(size(I));
        I(ruido_syp<parametro)=0;
        I(ruido_syp>1-parametro)=255;
end
        
        