package struct_test

import (
	"fmt"
	"testing"
)

type AnimalCategory struct {
	kingdom string
	phylum  string
	class   string
	order   string
	family  string
	genus   string
	species string
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

func TestAnimalCategory(t *testing.T) {
	category := AnimalCategory{species: "cat"}
	fmt.Printf("The animal category: %s\n", category)
	animal := Animal{
		scientificName: "American Shorthair",
		AnimalCategory: category,
	}
	cat := Cat{
		name:   "cat",
		Animal: animal,
	}
	fmt.Printf("The animal: %s\n", cat)
}
