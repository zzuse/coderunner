package struct_test

import (
	"fmt"
	"testing"
)

type AnimalCategory struct {
	kingdom string // 界。
	phylum  string // 门。
	class   string // 纲。
	order   string // 目。
	family  string // 科。
	genus   string // 属。
	species string // 种。
}

type Animal struct {
	scientificName string
	AnimalCategory
}

type Cat struct {
	name string
	Animal
}

func (ac AnimalCategory) String() string {
	return fmt.Sprintf("%s%s%s%s%s%s%s", ac.kingdom, ac.phylum, ac.class, ac.order, ac.family, ac.genus, ac.species)
}

func (a Animal) Category() string {
	return a.AnimalCategory.String()
}

func (a Animal) String() string {
	return fmt.Sprintf("%s (category:%s)", a.scientificName, a.AnimalCategory)
}

func (cat Cat) String() string {
	return fmt.Sprintf("%s (category: %s, name: %q)", cat.scientificName, cat.Animal.AnimalCategory, cat.name)
}

func New(name, scientificName, category string) Cat {
	categories := AnimalCategory{species: category}
	return Cat{
		name: name,
		Animal: Animal{
			scientificName: scientificName,
			AnimalCategory: categories,
		},
	}
}

func (cat *Cat) SetName(name string) {
	cat.name = name
}

func (cat Cat) SetNameOfCopy(name string) {
	cat.name = name
}

func (cat Cat) Name() string {
	return cat.name
}

func (cat Cat) ScientificName() string {
	return cat.scientificName
}

func (cat Cat) Category() string {
	return cat.Animal.AnimalCategory.String()
}

func TestAnimalCategory(t *testing.T) {
	category := AnimalCategory{species: "cat"}
	fmt.Printf("The animal category: %s\n", category)
	animal := Animal{
		scientificName: "American Shorthair",
		AnimalCategory: category,
	}
	cat := Cat{
		name:   "little pig",
		Animal: animal,
	}
	fmt.Printf("The cat: %s\n", cat)
}

func TestAnimalNew(t *testing.T) {
	cat := New("little pig", "American Shorthair", "cat")
	cat.SetName("monster")
	fmt.Printf("The cat 1: %s\n", cat)

	cat.SetNameOfCopy("little pig")
	fmt.Printf("The cat 2: %s\n", cat)
	fmt.Printf("The cat category: %s\n", cat.Category())

	type Pet interface {
		SetName(name string)
		Name() string
		Category() string
		ScientificName() string
	}

	_, ok := interface{}(cat).(Pet)
	fmt.Printf("Cat implements interface Pet: %v\n", ok)
	_, ok = interface{}(&cat).(Pet)
	fmt.Printf("&Cat implements interface Pet: %v\n", ok)
}
