# MuseumGuideAssistance
# Wstęp
Projekt utworzony w ramach zajęć inżynierskich. Współdziała z programem na telefony z systemem Android utworzonym w silniku UnrealEngine4 - https://github.com/iLuzj0/MuseumGuideAssistanceUE4

# Cel projektu
Projekt rozwiązuje problem oprowadzania wizytatora muzeum. Posiadacz smartfona może pobrać aplikacje na telefon, która na podstawie AprilTagów (https://roboticsknowledgebase.com/wiki/sensing/apriltags/) wyszukuje danego eksponatu w bazie danych. Wyszukiwanie oparte jest na technologiach implementowanych w OpenCV (https://opencv.org/). Serwer na komputerze stacjonarnym wysyła dane przez sieć za pomocą socketów UDP przez co smartfon wie na jaki eksponat aktualnie spogląda.

# Architekrura aplikacji
Na komputerze stacjonarnym jest stworzony serwer obsługujący obrazy przychodzące z smartfona, na którym zainstalowana jest aplikacja MuseumGuideAssistanceUE4. Przetworzone obrazy są następnie sprawdzane w bazie danych utworzonej w języku MySQL. Jeśli dany tag zostanie odnaleziony w bazie nasza aplikacja na telefonie pozwala nam odczytać informacje na temat specificznego eksponatu, któremu zrobiła właśnie zdjęcie.

# Dokumentacja
Dokumentacja wygenerowana za pomocą doxygen, znajduje się na stronie: https://iluzj0.github.io/MuseumGuideAssistance/
