\name{set.table}
\alias{set.table}

\title{Set Table}

\description{
Set the conditional probability table (CPT) of a node in an RHugin domain.
}

\usage{
set.table(domain, node, data)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{data}{a data frame (see details).}
}

\details{
The data frame containing the table must match Hugin's internal representation of the table data. The best way to do this is to use \code{get.table} to obtain a data frame with the proper layout, set the probabilities (frequencies) in the final column of this data frame and finally use \code{set.table} to set the table information in Hugin.  See the example.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_table_set_data} and \code{h_node_touch_table}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Add edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")

# Set the conditional probability table for Sick
sick.table <- get.table(AppleTree, "Sick")
sick.table$Freq <- c(0.1, 0.9)
set.table(AppleTree, "Sick", sick.table)
}

\keyword{programming}


