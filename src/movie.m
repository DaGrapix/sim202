
clear
clc
close all

%% Step 1: Importer les données 
%% On crée le vecteur temps 
t = linspace(0,100,1000);

%% On importe nos données à l'aide de la fonction readmatrix
P=readmatrix("C:/Users/mathi/OneDrive/Documents/ENSTA PARIS/Cours_deuxième_année/SIM202/successive_positions_N_100_NITER_1000_DT_0.100000.csv");

%% On récupère les dimensions de notre matrice : le nombre de lignes est notre nombre de particules tandis que le nombres de colonnes est 3 fois notre nombres d'itérations 

[N,temp]=size(P);
niter=temp/3;




%% Step 2: Dessiner les frames
% Création de la figure
figh = figure;
for k=1:niter
    %Nettoyer la figure pour commencer avec un fond vierge
    clf
    
    t_k=t(k);
    for i=1 :N
        
    % On prélève les coordonnées de la particule i au temps k
    
    
    x_k=P(i,1+3*(k-1));
    y_k=P(i,2+3*(k-1));
    z_k=P(i,3+3*(k-1));
    
  
    %On va plot en 3D notre point avec un cas différent si c'est notre
    %première ou dernière particule et les autres.
    if i==1 
        
        plot3(x_k, y_k, z_k,'w.')
        % On utilise hold on pour plot tous les points sur un même
        % graphique
        hold on
    elseif i==N
        
            plot3(x_k, y_k, z_k,"w.")
            %On relâche notre graphique à la dernière particule
            hold off
    else 
            plot3(x_k, y_k, z_k,"w.")


    end
    end
    
       
            

    %On change la couleur de fond au noir 
    
    set(gca,'color','k');
   

    
   % On ajoute des options au titre 
    xlabel('x')
    ylabel('y')
    zlabel('z')
    axis([-1000 1000 -600 500 -500 600]);
    %view([30 35])
    title(['Our galaxy at t = ',num2str(t_k)])
    %% Step 3: Prendre une Snapshot
    %Sauvegarder la frame 
    frame(k) = getframe(figh, [10 10 520 400]);   % on spécifie manuellement la région pour getframe 
    
    
end

%% Step 5: Save Movie
%On crée un objet video writer 
myWriter = VideoWriter('Galaxy');            %Créé un fichier .avi 

myWriter.FrameRate = 20;

% On ouvre l'objet VideoWriter, on écrit le film dedans puis on le ferme.
open(myWriter);
writeVideo(myWriter, frame);
close(myWriter);

disp('DONE!')