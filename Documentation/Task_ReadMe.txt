{
	// Task wird nur geladen, wenn kein Task mit identischem Namen geladen ist
	"taskName": "string",

	// Taskart hier angeben, leere List wird nicht akzeptiert
	"taskType": ["string",...], 

	// Projektname muss immer vorhanden sein, da immer ein Projekt geladen wird
	"projectName": "string", 

	// Taskarten können verodert werden, also ["addProject","imageLoad","split","training","classification"] ist eine valide Kombination
}



Folgende Tasks sind möglich:

// AddProjectTask ("addProject")
// Erstellt ein neues Projekt, falls dieses nicht bereits existiert
{
	"taskName": "string",
	"taskType": ["addProject"],
	"projectName": "string"
}

// ImageLoadTask ("imageLoad")
// Lädt Bilder in das temporäre Bildverzeichnis eines Projekts
{
	"taskName": "string",
	"taskType": ["imageLoad"],
	"projectName": "string",
	
	// Name des verwendeten Bildladerplugins
	"imagePluginName": "string",
	
	// Anzahl der Bilder pro Label	
	"count": int,
	
	// Liste von Labels nach denen gesucht wird
	"labels": ["string", "string", "string", ...]
}

// SplitTask ("split")
// Verteilt Bilder von temporärem Bildorder in Trainings- und Validierungsbilder auf
{
	"taskName": "string",
	"taskType": ["split"],
	"projectName": "string",

	// Anzahl der Bilder in Prozent, die als Validierungsbilder verwendet werden
	// Falls das Argument ungültig ist oder der Eintrag fehlt, wird mit 30% gerechnet	 
	"split": int
}


// TrainingTask ("training")
// Führt ein Training aus
{
	"taskName": "string",
	"taskType": ["training"],
	"projectName": "string",

	// Name des ausgewählten Modells
	"modelName": "string",

	// Name des ausgewählten Trainings-/Klassifizierungsplugins
	"aiPluginName": "string"
}

//ClassificationTask ("classification")
// Führt eine Klassifizierung aus
{
	"taskName": "string",
	"taskType": ["classification"],
	"projectName": "string",

	// Ordner mit Bildern zur Klassifizierung
	"classificationImagePath": "string",

	// Name des ausgewählten Modells
	"modelName": "string",

	// Name des ausgewählten Trainings-/Klassifizierungsplugins
	"aiPluginName": "string"
}



Generell funktioniert des bei kombinierten tasks so, dass Dinge mit gleichem Namen nur einmal vorkommen,
also wenn man zB Training und Klassifizierung kombiniert gilt "aiPluginName" für beides
und muss auch nur einmal angegeben werden.


Plugin spezifische Einstellungen:
	Falls ein Plugin mehr/andere Informationen als die oben möglichen braucht, ist es mögliche diese
	mittels Q_PROPERTY Makro zu kennzeichnen und entsprechende Getter und Setter zu definieren. 
	Der Eintrag in der Json Datei entspricht dem Namen der betroffenen Eigenschaft.

	FolderPlugin:
		// Auf welche Weise soll geladen werden
		// 0 = Unterordner als Labels
		// 1 = Labels aus "label_" in Dateiname
		// 2 = Order als ein Label
		// Standardwert 0
		"loadMode": int,

		// Ordner aus dem die Bilder/Unterorder geladen werden sollen
		"imageFolder": "string"


	MMClassification:
		// alle folgendenen Eigenschaften haben einen Standardwert

		// Input Widget Optionen 
		"m_max_iters": int,
		"m_cuda_device": int,

		// Data Augmentation Optionen
		"m_albu_transform_type" = "string",
    		"m_random_flip_prob" = double,
    		"m_random_flip_direction" = "string",
    		"m_randomErasing" = boolean,
    		"m_resize" = int,
    		"m_center_crop_size" = int		

		 