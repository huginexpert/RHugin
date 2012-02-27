\name{set.table}
\alias{set.table}

\title{Set Table}

\description{
Set the conditional probability table (CPT), experience table or fading table of a node in an RHugin domain.
}

\usage{
set.table(domain, node, data, type = c("cpt", "experience", "fading"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{data}{a data frame, table or numeric vector (see details).}
  \item{type}{a character string specifying the type of table to set.}
}

\details{
The \code{data} argument may be a data frame, table, or (for discrete nodes) a numeric vector.  When \code{data} is a data frame, RHugin attempts to rearrange its rows and columns so that it matches Hugin's internal representation of the table data.  A side effect is that RHugin will compute the appropriate marginal table when the data frame provided in \code{data} has more variables than the actual table of \code{node}.  See the example.  When \code{data} is a table, the dimension and dimnames attribute must match those of the table of \code{node}.  When \code{data} is a numeric vector the user is responsible for having the table data in the correct order.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_table_get_data}, \code{h_node_touch_table}, \code{h_node_set_alpha}, \code{h_node_set_beta} and \code{h_node_set_gamma}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
# (1) Set the CPT of a single node

# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add edges
add.edge(apple, "Loses", "Sick")
add.edge(apple, "Loses", "Dry")

# Set the conditional probability table for Sick
sick.table <- get.table(apple, "Sick")
sick.table$Freq <- c(0.1, 0.9)
set.table(apple, "Sick", sick.table)


# (2) Set the CPTs for all nodes in a domain using the
# marginal counts from a data frame

library(MASS)
data(housing)

# First build the network
hd <- hugin.domain(data = housing)
add.edge(hd, "Cont", "Type")
add.edge(hd, "Sat", "Cont")
add.edge(hd, "Sat", "Infl")

# Then set the CPTs
for(node in get.nodes(hd)) set.table(hd, node, housing)


# (3) RHugin reorders the rows and columns of the data frame
# to match Hugin's internal representation of the table data

Cont.table <- get.table(hd, "Cont")
set.seed(10)
temp <- Cont.table[sample(8), ]
temp <- temp[c("Type", "Cont", "Freq")]
temp

set.table(hd, "Cont", temp)
all.equal(Cont.table, get.table(hd, "Cont"))
}

\keyword{programming}


